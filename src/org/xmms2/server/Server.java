package org.xmms2.server;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.Service;
import android.content.*;
import android.media.AudioManager;
import android.os.*;

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

    private static final Queue<Messenger> queue = new LinkedList<Messenger>();

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

    private void serverReady()
    {
        synchronized (queue) {
            running = true;
            MessageHandler.running = true;
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

        mediaButtonEventHandler = new ComponentName(this, MediaButtonEventHandler.class);
        audioManager.registerMediaButtonEventReceiver(mediaButtonEventHandler);

        statusHandler = new StatusHandler();
        metadataHandler = new MetadataHandler(this);

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
                    MessageHandler.running = false;
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

    @SuppressLint("NewApi")
    private String getPluginPath()
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.GINGERBREAD) {
            return getApplicationInfo().nativeLibraryDir;
        } else {
            return getApplicationInfo().dataDir + "/lib";
        }
    }

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
