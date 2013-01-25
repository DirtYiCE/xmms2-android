package org.xmms2.server;

import android.app.Notification;
import android.app.Service;
import android.content.*;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.os.*;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.channels.ReadableByteChannel;
import java.util.LinkedList;
import java.util.Queue;


/**
 * @author Eclipser
 */
public class Server extends Service implements NotificationUpdater
{
    public static final int ONGOING_NOTIFICATION = 1;
    public static final String ACTION_START_CLIENT = "org.xmms2.server.action.START_CLIENT";
    private HeadsetReceiver headsetReceiver;
    private Thread serverThread;
    private String pluginPath;
    private boolean running;
    private static boolean storageAvailable;
    private BroadcastReceiver storageStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            updateExternalStorageState();
        }
    };
    private MediaObserver mediaObserver;
    private AudioManager audioManager;

    private final Queue<Messenger> queue = new LinkedList<Messenger>();

    // these handlers are used from native side
    private StatusHandler statusHandler;
    @SuppressWarnings("FieldCanBeLocal")
    private MetadataHandler metadataHandler;

    private NotificationHandler notificationHandler;
    private RemoteControl remoteControl = null;

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

    public void registerHeadsetListener(HeadsetListener listener)
    {
        headsetReceiver.registerHeadsetListener(listener);
    }

    public void registerFocusListener(AudioFocusHandler focusHandler)
    {
        focusHandler.registerFocusListener(headsetReceiver);
    }

    class MessageHandler extends Handler
    {
        static final int MSG_START = 1;

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

    private void notifyClient(Messenger messenger)
    {
        Bundle bundle = new Bundle();
        bundle.putBoolean("running", running);
        bundle.putString("address", "tcp://localhost:9667");
        Message reply = Message.obtain(null, MessageHandler.MSG_START);
        reply.setData(bundle);
        try {
            messenger.send(reply);
        } catch (RemoteException ignored) {}
    }

    private void serverReady()
    {
        synchronized (queue) {
            running = true;
            Messenger messenger = queue.poll();
            while (messenger != null) {
                notifyClient(messenger);
                messenger = queue.poll();
            }
        }
    }

    static native void play();
    static native void pause();
    static native void stop();
    static native void toggle();
    static native void next();
    static native void previous();

    private native void start();
    private native void quit();

    private ComponentName mediaButtonEventHandler;

    @Override
    public void onCreate()
    {
        super.onCreate();

        IntentFilter filter = new IntentFilter();
        filter.addAction(Intent.ACTION_MEDIA_MOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_REMOVED);
        registerReceiver(storageStateReceiver, filter);

        mediaObserver = new MediaObserver(Environment.getExternalStorageDirectory().getAbsolutePath());
        audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        File pluginsDirOut = new File(getFilesDir(), "/plugins/");
        pluginPath = pluginsDirOut.getAbsolutePath();
        if (!pluginsDirOut.exists() && !pluginsDirOut.mkdirs()) {
            throw new RuntimeException();
        }

        AssetManager am = getResources().getAssets();

        try {
            for (String plugin : am.list("plugins")) {
                File out = new File(pluginsDirOut, plugin);
                if (out.exists()) {
                    continue;
                }

                InputStream stream = am.open("plugins/" + plugin, AssetManager.ACCESS_RANDOM);
                long length = stream.skip(Long.MAX_VALUE);

                copyFile(am.open("plugins/" + plugin), out, length);
            }
        } catch (IOException ignored) {}

        mediaButtonEventHandler = new ComponentName(this, MediaButtonEventHandler.class);
        audioManager.registerMediaButtonEventReceiver(mediaButtonEventHandler);

        statusHandler = new StatusHandler();
        metadataHandler = new MetadataHandler();

        notificationHandler = new NotificationHandler(this, this);
        statusHandler.registerPlaybackStatusListener(notificationHandler);
        metadataHandler.registerMetadataListener(notificationHandler);

        remoteControl = new RemoteControl(this, mediaButtonEventHandler);
        statusHandler.registerPlaybackStatusListener(remoteControl);
        metadataHandler.registerMetadataListener(remoteControl);

        headsetReceiver = new HeadsetReceiver(audioManager.isSpeakerphoneOn() ? HeadsetState.UNPLUGGED : HeadsetState.PLUGGED);
        statusHandler.registerPlaybackStatusListener(headsetReceiver);

        filter = new IntentFilter();
        filter.addAction(AudioManager.ACTION_AUDIO_BECOMING_NOISY);
        filter.addAction(Intent.ACTION_HEADSET_PLUG);
        registerReceiver(headsetReceiver, filter);
    }

    private static void copyFile(InputStream input, File output, long length) throws IOException
    {
        if (!output.exists() && !output.createNewFile()) {
            throw new IOException("Could not create file");
        }

        ReadableByteChannel source = null;
        FileChannel destination = null;

        try {
            source = Channels.newChannel(input);
            destination = new FileOutputStream(output).getChannel();
            destination.transferFrom(source, 0, length);
        } finally {
            if (source != null) {
                source.close();
            }
            if (destination != null) {
                destination.close();
            }
        }
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
                    start();
                    running = false;
                    stopForeground(true);
                    mediaObserver.stopWatching();
                    stopSelf();
                }
            });

            serverThread.start();
        }
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy()
    {
        stopForeground(true);
        mediaObserver.stopWatching();
        audioManager.unregisterMediaButtonEventReceiver(mediaButtonEventHandler);
        notificationHandler.unregisterReceiver();
        remoteControl.unregister();
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

    private String getPluginPath()
    {
        return pluginPath;
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
