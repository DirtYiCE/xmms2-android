package org.xmms2.server;

import android.app.PendingIntent;
import android.app.Service;
import android.content.*;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.AudioManager;
import android.media.MediaMetadataRetriever;
import android.media.RemoteControlClient;
import android.os.*;
import android.support.v4.app.NotificationCompat;
import android.widget.RemoteViews;

import java.io.*;
import java.net.URLDecoder;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.channels.ReadableByteChannel;
import java.util.LinkedList;
import java.util.Queue;


/**
 * @author Eclipser
 */
public class Server extends Service
{
    public static final int ONGOING_NOTIFICATION = 1;
    public static final String ACTION_START_CLIENT = "org.xmms2.server.action.START_CLIENT";
    private static final String ACTION_TOGGLE_PLAYBACK = "org.xmms2.server.action.TOGGLE_PLAYBACK";
    private static final String ACTION_NEXT = "org.xmms2.server.action.NEXT";
    private static final String ACTION_STOP_PLAYBACK = "org.xmms2.server.action.STOP_PLAYBACK";
    private Thread serverThread;
    private String pluginPath;
    private boolean running;
    private int oldStatus;
    private int status;
    private static boolean storageAvailable;
    private BroadcastReceiver storageStateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            updateExternalStorageState();
        }
    };
    private MediaObserver mediaObserver;
    private PlaybackStatusListener playbackStatusListener;
    private boolean focusLost = false;
    private boolean headset = false;
    private AudioManager audioManager;
    private boolean ducked;

    private final Queue<Messenger> queue = new LinkedList<Messenger>();
    private String url;
    private String title;
    private String artist;
    private PendingIntent clientStartIntent;
    private RemoteViews notificationView;
    private final BroadcastReceiver notificationActionReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            if (ACTION_TOGGLE_PLAYBACK.equals(intent.getAction())) {
                if (status == 1) {
                    pause();
                } else if (status == 2) {
                    play();
                }
            } else if (ACTION_STOP_PLAYBACK.equals(intent.getAction())) {
                stop();
            } else if (ACTION_NEXT.equals(intent.getAction())) {
                next();
            }
        }
    };

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

    private AudioManager.OnAudioFocusChangeListener audioFocusChangeListener = new AudioManager.OnAudioFocusChangeListener()
    {
        @Override
        public void onAudioFocusChange(int focusChange)
        {
            if (focusChange == AudioManager.AUDIOFOCUS_GAIN) {
                if (ducked) {
                    playbackStatusListener.adjustVolume(1.0f, 1.0f);
                    ducked = false;
                }

                if (!audioManager.isSpeakerphoneOn() && headset && focusLost && oldStatus == 1) {
                    play();
                }
                focusLost = false;
            } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS || focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT) {
                focusLost = true;
                if (status == 1) {
                    pause();
                }
            } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK) {
                ducked = true;
                playbackStatusListener.adjustVolume(0.1f, 0.1f);
            }
        }
    };

    private BroadcastReceiver headsetReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            if (!running) {
                return;
            }
            if (AudioManager.ACTION_AUDIO_BECOMING_NOISY.equals(intent.getAction())) {
                if (status == 1) {
                    pause();
                }
                headset = false;
            } else if (Intent.ACTION_HEADSET_PLUG.equals(intent.getAction()) &&
                       intent.getExtras().getInt("state") == 1) {
                if (!focusLost && oldStatus == 1) {
                    play();
                }
                headset = true;
            }
        }
    };

    static native void play();
    static native void pause();
    static native void stop();
    static native void toggle();
    static native void next();
    static native void previous();

    private native void start();
    private native void quit();

    private ComponentName mediaButtonEventHandler;
    private RemoteControlClient remoteControlClient;

    @Override
    public void onCreate()
    {
        super.onCreate();
        Intent intent = new Intent(ACTION_START_CLIENT);
        intent.putExtra("address", "tcp://localhost:9667");
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        clientStartIntent = PendingIntent.getActivity(getApplicationContext(), 0, intent, 0);

        notificationView = new RemoteViews(getPackageName(), R.layout.notification);
        Intent toggle = new Intent(ACTION_TOGGLE_PLAYBACK);
        notificationView.setOnClickPendingIntent(R.id.toggle,
                                                 PendingIntent.getBroadcast(getApplicationContext(), 0, toggle, 0));

        Intent next = new Intent(ACTION_NEXT);
        notificationView.setOnClickPendingIntent(R.id.next,
                                                 PendingIntent.getBroadcast(getApplicationContext(), 0, next, 0));

        Intent stop = new Intent(ACTION_STOP_PLAYBACK);
        notificationView.setOnClickPendingIntent(R.id.close,
                                                 PendingIntent.getBroadcast(getApplicationContext(), 0, stop, 0));

        IntentFilter notificationActionFilter = new IntentFilter();
        notificationActionFilter.addAction(ACTION_TOGGLE_PLAYBACK);
        notificationActionFilter.addAction(ACTION_NEXT);
        notificationActionFilter.addAction(ACTION_STOP_PLAYBACK);
        registerReceiver(notificationActionReceiver, notificationActionFilter);

        IntentFilter filter = new IntentFilter();
        filter.addAction(Intent.ACTION_MEDIA_MOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_UNMOUNTED);
        filter.addAction(Intent.ACTION_MEDIA_REMOVED);
        registerReceiver(storageStateReceiver, filter);

        filter = new IntentFilter();
        filter.addAction(AudioManager.ACTION_AUDIO_BECOMING_NOISY);
        filter.addAction(Intent.ACTION_HEADSET_PLUG);
        registerReceiver(headsetReceiver, filter);

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
        // build the PendingIntent for the remote control client
        Intent mediaButtonIntent = new Intent(Intent.ACTION_MEDIA_BUTTON);
        mediaButtonIntent.setComponent(mediaButtonEventHandler);
        PendingIntent mediaPendingIntent = PendingIntent.getBroadcast(getApplicationContext(), 0, mediaButtonIntent, 0);

        // create and register the remote control client
        remoteControlClient = new RemoteControlClient(mediaPendingIntent);
        remoteControlClient.setTransportControlFlags(RemoteControlClient.FLAG_KEY_MEDIA_NEXT |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_PREVIOUS |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_PLAY_PAUSE |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_STOP);
        audioManager.registerMediaButtonEventReceiver(mediaButtonEventHandler);
        audioManager.registerRemoteControlClient(remoteControlClient);
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
        audioManager.unregisterRemoteControlClient(remoteControlClient);
        unregisterReceiver(notificationActionReceiver);
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

    private void setCurrentlyPlayingInfo(String url, String artist, String title)
    {
        try {
            this.url = new File(URLDecoder.decode(url, "UTF-8")).getName();
        } catch (UnsupportedEncodingException e) {
            this.url = url;
        }
        this.title = title;
        this.artist = artist;
        updateNotification();
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.logo);
        remoteControlClient.editMetadata(true).putString(MediaMetadataRetriever.METADATA_KEY_ARTIST, artist)
                                              .putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, bitmap)
                                              .putString(MediaMetadataRetriever.METADATA_KEY_TITLE, title).apply();
    }

    private void updateStatus(int status)
    {
        this.oldStatus = this.status;
        this.status = status;
        if (playbackStatusListener != null) {
            playbackStatusListener.playbackStatusChanged(status);
        }
        if (status == 0) {
            stopForeground(true);
            remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_STOPPED);
        } else {
            remoteControlClient.setPlaybackState(status == 1 ? RemoteControlClient.PLAYSTATE_PLAYING : RemoteControlClient.PLAYSTATE_PAUSED);
            notificationView.setImageViewResource(R.id.toggle, status == 1 ? R.drawable.pause : R.drawable.play);
            updateNotification();
        }
    }

    private void updateNotification()
    {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this);
        builder.setContentIntent(clientStartIntent);
        builder.setContent(notificationView);
        builder.setContentTitle(title != null ? title : url);
        notificationView.setTextViewText(R.id.title, title != null ? title : url);
        builder.setContentText(artist);
        notificationView.setTextViewText(R.id.artist, artist != null ? artist : "");
        builder.setContentInfo(stringStatus(status));
        builder.setTicker(createTicker());
        builder.setOngoing(true);
        builder.setSound(null);
        builder.setSmallIcon(R.drawable.notification);

        startForeground(ONGOING_NOTIFICATION, builder.build());
    }

    private String createTicker()
    {
        if (artist == null && title == null) {
            return url;
        } else if (artist == null) {
            return title;
        } else if (title == null) {
            return artist;
        }
        return String.format("%s - %s", artist, title);
    }

    private String stringStatus(int status)
    {
        switch (status) {
            case 0:
                return "Stopped";
            case 1:
                return "Playing";
            case 2:
                return "Paused";
            default:
                return "Unknown";
        }
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
        this.playbackStatusListener = playbackStatusListener;
    }

    public AudioManager.OnAudioFocusChangeListener getAudioFocusChangeListener()
    {
        return audioFocusChangeListener;
    }
}
