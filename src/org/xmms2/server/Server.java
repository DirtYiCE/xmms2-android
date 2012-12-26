package org.xmms2.server;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.os.Build;
import android.os.Environment;
import android.os.IBinder;
import org.xmms2.server.api11.NotificationFactoryLevel11;
import org.xmms2.server.api8.NotificationFactoryLevel8;

import java.io.*;
import java.net.URLDecoder;
import java.nio.channels.Channels;
import java.nio.channels.FileChannel;
import java.nio.channels.ReadableByteChannel;


/**
 * @author Eclipser
 */
public class Server extends Service
{
    public static final int ONGOING_NOTIFICATION = 1;
    private static final String ACTION_SERVER_STATUS = "org.xmms2.server.action.SERVER_STATUS";
    private static final String ACTION_START_CLIENT = "org.xmms2.server.action.START_CLIENT";
    private NotificationFactory notificationFactory;
    private Thread serverThread;
    private String pluginPath;
    private boolean running;
    private String nowPlaying;
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

    private native void play();
    private native void pause();

    private native void start();
    private native void quit();

    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
        removeStickyBroadcast(new Intent(ACTION_SERVER_STATUS));
        Intent intent = new Intent(ACTION_START_CLIENT);
        intent.putExtra("address", "tcp://127.0.0.1:9667");
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        PendingIntent pendingIntent = PendingIntent.getActivity(getApplicationContext(), 0, intent, 0);

        if (Build.VERSION.SDK_INT >= 11) {
            notificationFactory = new NotificationFactoryLevel11(getApplicationContext(), pendingIntent);
        } else { // min SDK version 8 in manifest
            notificationFactory = new NotificationFactoryLevel8(getApplicationContext(), pendingIntent);
        }

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
        if (!running && storageAvailable) {
            serverThread = new Thread(new Runnable()
            {
                @Override
                public void run()
                {
                    start();
                    running = false;
                    stopForeground(true);
                    removeStickyBroadcast(new Intent(ACTION_SERVER_STATUS));
                    mediaObserver.stopWatching();
                    stopSelf();
                }
            });

            serverThread.start();
            running = true;
        }
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy()
    {
        if (running) {
            quit();
            try {
                serverThread.join();
            } catch (InterruptedException ignored) {}
        }
        stopForeground(true);
        mediaObserver.stopWatching();
        unregisterReceiver(storageStateReceiver);
        unregisterReceiver(headsetReceiver);
        removeStickyBroadcast(new Intent(ACTION_SERVER_STATUS));
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
        if (artist == null && title == null) {
            try {
                url = new File(URLDecoder.decode(url, "UTF-8")).getName();
            } catch (UnsupportedEncodingException ignored) {}
            nowPlaying = url;
        } else if (artist == null) {
            nowPlaying = title;
        } else if (title == null) {
            nowPlaying = artist;
        } else {
            nowPlaying = String.format("%s - %s", artist, title);
        }
        updateNotification();
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
        } else {
            updateNotification();
        }
    }

    private void updateNotification()
    {
        Notification note = notificationFactory.getNotification("XMMS2", nowPlaying, nowPlaying, stringStatus(status));
        startForeground(ONGOING_NOTIFICATION, note);
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

    private void serverReady()
    {
        Intent intent = new Intent(ACTION_SERVER_STATUS);
        intent.putExtra("running", true);
        intent.putExtra("address", "tcp://localhost:9667");
        sendStickyBroadcast(intent);

        mediaObserver.startWatching();
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
