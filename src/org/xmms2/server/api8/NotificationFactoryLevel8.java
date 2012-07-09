package org.xmms2.server.api8;

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import org.xmms2.server.NotificationFactory;
import org.xmms2.server.R;

/**
 * @author Eclipser
 */
public class NotificationFactoryLevel8 implements NotificationFactory
{
    private final Context context;
    private final PendingIntent pendingIntent;

    public NotificationFactoryLevel8(Context context, PendingIntent pendingIntent)
    {
        this.context = context;
        this.pendingIntent = pendingIntent;
    }

    @Override
    public Notification getNotification(String title, String text, String ticker, String info)
    {
        Notification notification = new Notification(R.drawable.notification, ticker, System.currentTimeMillis());
        notification.setLatestEventInfo(context, String.format("%s %s", title, info), text, pendingIntent);
        notification.sound = null;

        return notification;
    }
}
