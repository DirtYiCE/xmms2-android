package org.xmms2.server;

import android.app.Notification;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import org.xmms2.server.api11.NotificationFactoryLevel11;
import org.xmms2.server.api8.NotificationFactoryLevel8;

/**
 * @author Eclipser
 */
public class Server extends Service
{
    public static final int ONGOING_NOTIFICATION = 1;
    private NotificationFactory notificationFactory;

    private native void start();

    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public void onCreate()
    {
        super.onCreate();

        if (Build.VERSION.SDK_INT >= 11) {
            notificationFactory = new NotificationFactoryLevel11(getApplicationContext());
        } else { // min SDK version 8 in manifest
            notificationFactory = new NotificationFactoryLevel8(getApplicationContext());
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        Notification notification = notificationFactory.create();
        startForeground(ONGOING_NOTIFICATION, notification);
        start();
        return START_STICKY;
    }

    static {
        System.loadLibrary("glib-2.0");
        System.loadLibrary("gmodule-2.0");
        System.loadLibrary("gthread-2.0");
        System.loadLibrary("xmms2");
    }
}
