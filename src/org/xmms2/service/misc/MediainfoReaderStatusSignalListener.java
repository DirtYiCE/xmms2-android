package org.xmms2.service.misc;

import android.app.NotificationManager;
import android.content.Context;
import android.os.Handler;
import android.support.v4.app.NotificationCompat;
import org.xmms2.eclipser.client.commands.SignalListener;
import org.xmms2.eclipser.client.protocol.types.MediainfoReaderStatus;
import org.xmms2.server.R;

import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
* @author Eclipser
*/
class MediainfoReaderStatusSignalListener implements SignalListener<MediainfoReaderStatus>
{
    private final NotificationManager notificationManager;
    private final NotificationCompat.Builder builder;
    private final Handler handler;
    private final ScheduledExecutorService scheduler = new ScheduledThreadPoolExecutor(1);
    private ScheduledFuture<?> task;
    private static final int MEDIA_INFO_NOTIFICATION = 2;
    private boolean showingNotification = false;

    public MediainfoReaderStatusSignalListener(Context context)
    {
        notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        builder = new NotificationCompat.Builder(context);
        builder.setContentTitle(context.getString(R.string.indexing_title))
               .setContentText(context.getString(R.string.indexing_process_text))
               .setProgress(0, 0, true)
               .setOngoing(true)
               .setSmallIcon(R.drawable.notification);
        handler = new Handler();
    }

    @Override
    public int handleSignal(MediainfoReaderStatus mediainfoReaderStatus)
    {
        if (task != null && !task.isDone()) {
            task.cancel(true);
            task = null;
        } else if (mediainfoReaderStatus == MediainfoReaderStatus.RUNNING && !showingNotification) {
            task = scheduler.schedule(new Runnable()
            {
                @Override
                public void run()
                {
                    showNotification();
                }
            }, 1, TimeUnit.SECONDS);
        } else if (mediainfoReaderStatus == MediainfoReaderStatus.IDLE && showingNotification) {
            task = scheduler.schedule(new Runnable()
            {
                @Override
                public void run()
                {
                    removeNotification();
                }
            }, 1, TimeUnit.SECONDS);
        }
        return 0;
    }

    void removeNotification()
    {
        handler.post(new Runnable()
        {
            @Override
            public void run()
            {
                notificationManager.cancel(MEDIA_INFO_NOTIFICATION);
                showingNotification = false;
            }
        });
    }

    private void showNotification()
    {
        handler.post(new Runnable()
        {
            @Override
            public void run()
            {
                notificationManager.notify(MEDIA_INFO_NOTIFICATION, builder.build());
                showingNotification = true;
            }
        });
    }
}
