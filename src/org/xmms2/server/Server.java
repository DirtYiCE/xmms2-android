package org.xmms2.server;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.media.AudioManager;
import android.os.*;
import android.util.Log;
import android.widget.Toast;
import org.xmms2.service.medialib.updater.UpdaterService;
import org.xmms2.service.misc.MiscClient;
import org.xmms2.service.misc.NotificationUpdater;

import java.io.*;
import java.lang.Process;
import java.util.LinkedList;
import java.util.Queue;


/**
 * @author Eclipser
 */
public class Server extends Service
{
    public static final int ONGOING_NOTIFICATION = 1;
    public static final String ACTION_START_CLIENT = "org.xmms2.server.action.START_CLIENT";
    private HeadsetReceiver headsetReceiver;
    private Thread serverThread;
    private boolean running;
    private static boolean storageAvailable;
    private BroadcastReceiver storageStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            updateExternalStorageState();
        }
    };

    private static final Queue<Messenger> queue = new LinkedList<Messenger>();

    // these handlers are used from native side
    private StatusHandler statusHandler;

    private MiscClient metadataClient;

    private final NotificationUpdater notificationUpdater = new NotificationUpdater()
    {
        @Override
        public void updateNotification(Notification notification)
        {
            startForeground(ONGOING_NOTIFICATION, notification);
        }

        @Override
        public void removeNotification()
        {
            stopForeground(true);
        }
    };
    private Handler handler;

    public void registerHeadsetListener(HeadsetListener listener)
    {
        headsetReceiver.registerHeadsetListener(listener);
    }

    public void registerFocusListener(AudioFocusHandler focusHandler)
    {
        focusHandler.registerFocusListener(headsetReceiver);
    }

    static class MessageHandler extends Handler
    {
        static final int MSG_START = 1;
        static boolean running;

        @Override
        public void handleMessage(Message msg)
        {
            if (msg.what == MSG_START && msg.replyTo != null) {
                synchronized (queue) {
                    if (running) {
                        notifyClient(msg.replyTo);
                    } else {
                        queue.add(msg.replyTo);
                    }
                }
            } else {
                super.handleMessage(msg);
            }
        }
    }

    private final Messenger messenger = new Messenger(new MessageHandler());

    @Override
    public IBinder onBind(Intent intent)
    {
        startService(new Intent(this, Server.class));
        return messenger.getBinder();
    }

    private static void notifyClient(Messenger messenger)
    {
        Bundle bundle = new Bundle();
        bundle.putBoolean("running", MessageHandler.running);
        bundle.putString("address", "tcp://localhost:9667");
        Message reply = Message.obtain(null, MessageHandler.MSG_START);
        reply.setData(bundle);
        try {
            messenger.send(reply);
        } catch (RemoteException ignored) {}
    }

    @SuppressWarnings("UnusedDeclaration")
    private void serverReady()
    {
        synchronized (queue) {
            running = true;
            startServiceClients();
            MessageHandler.running = true;
            Messenger messenger = queue.poll();
            while (messenger != null) {
                notifyClient(messenger);
                messenger = queue.poll();
            }
        }
    }

    private void startServiceClients()
    {
        handler.post(new Runnable()
        {
            @Override
            public void run()
            {
                try {
                    metadataClient = new MiscClient("tcp://localhost:9667", Server.this, notificationUpdater);
//                    startService(new Intent(Server.this, UpdaterService.class));
                } catch (IOException e) {
                    Toast.makeText(Server.this, R.string.service_client_error, Toast.LENGTH_SHORT);
                }
            }
        });
    }

    private void stopServiceClients()
    {
        if (metadataClient != null) {
            metadataClient.disconnect();
        }
    }

    static native void play();
    static native void pause();

    private native void start();
    private native void quit();

    @Override
    public void onCreate()
    {
        super.onCreate();

        handler = new Handler();
        IntentFilter filter = new IntentFilter();
        filter.addAction(Intent.ACTION_MEDIA_MOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_REMOVED);
        registerReceiver(storageStateReceiver, filter);

        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        statusHandler = new StatusHandler();

        headsetReceiver = new HeadsetReceiver(audioManager.isSpeakerphoneOn() ? HeadsetState.UNPLUGGED : HeadsetState.PLUGGED);
        statusHandler.registerPlaybackStatusListener(headsetReceiver);

        filter = new IntentFilter();
        filter.addAction(AudioManager.ACTION_AUDIO_BECOMING_NOISY);
        filter.addAction(Intent.ACTION_HEADSET_PLUG);
        registerReceiver(headsetReceiver, filter);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        updateExternalStorageState();
        if ((serverThread == null || !serverThread.isAlive()) && storageAvailable) {
            serverThread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    try {
                        runMigrateCollections();
                        start();
                    } catch (InterruptedException ignored) {}
                    MessageHandler.running = false;
                    running = false;
                    stopForeground(true);
                    stopServiceClients();
                    stopSelf();
                }
            });

            serverThread.start();
        }
        return START_NOT_STICKY;
    }

    private void runMigrateCollections() throws InterruptedException
    {
        if (getExternalFilesDir(null) == null) return;
        File conf = new File(getConfigDir(), "config");
        File collections = new File(conf, "collections");
        if (conf.exists() && conf.isDirectory() && collections.exists() && collections.isDirectory()) {
            File[] files = collections.listFiles(new FilenameFilter()
            {
                @Override
                public boolean accept(File dir, String filename)
                {
                    return !filename.endsWith(".legacy") && new File(dir, filename).isDirectory();
                }
            });

            File workingDirectory = new File(getPluginPath());
            String migrateCollections = "migrate-collections";
            String exec = workingDirectory.getAbsolutePath() + "/libtool-runner.so";

            for (File file : files) {
                Log.d("XMMS2", "Running " + migrateCollections + " " + file.getAbsolutePath());
                try {
                    Process process = new ProcessBuilder()
                                    .directory(workingDirectory)
                                    .command(exec, workingDirectory.getAbsolutePath(), migrateCollections, file.getAbsolutePath())
                                    .redirectErrorStream(true)
                                    .start();

                    BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
                    int read;
                    char[] buffer = new char[4096];
                    StringBuilder output = new StringBuilder();
                    while ((read = reader.read(buffer)) > 0) {
                        output.append(buffer, 0, read);
                    }
                    reader.close();
                    process.waitFor();
                    Log.d("XMMS2", output.toString());
                } catch (IOException e) {
                    Log.e("XMMS2", e.getMessage(), e);
                }
            }
        }
    }

    @Override
    public void onDestroy()
    {
        stopForeground(true);
        stopServiceClients();
        unregisterReceiver(storageStateReceiver);
        unregisterReceiver(headsetReceiver);
        if (running) {
            quit();
            try {
                serverThread.join();
            } catch (InterruptedException ignored) {}
        }
    }

    // Should probably use Context.getFilesDir()
    private String getConfigDir()
    {
        return getExternalFilesDir(null).getAbsolutePath();
    }

    @SuppressLint("NewApi")
    private String getPluginPath()
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.GINGERBREAD) {
            return getApplicationInfo().nativeLibraryDir;
        } else {
            return getApplicationInfo().dataDir + "/lib";
        }
    }

    @SuppressWarnings("UnusedDeclaration")
    private String getBrowseRoot()
    {
        return Environment.getExternalStorageDirectory().getAbsolutePath();
    }

    public static void updateExternalStorageState()
    {
        String state = Environment.getExternalStorageState();
        storageAvailable = Environment.MEDIA_MOUNTED.equals(state);
    }

    static {
        System.loadLibrary("glib-2.0");
        System.loadLibrary("gmodule-2.0");
        System.loadLibrary("gthread-2.0");
        System.loadLibrary("xmms2");
    }

    public void registerPlaybackListener(PlaybackStatusListener playbackStatusListener)
    {
        statusHandler.registerPlaybackStatusListener(playbackStatusListener);
    }
}
