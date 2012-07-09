package org.xmms2.server.api11;

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import org.xmms2.server.NotificationFactory;
import org.xmms2.server.R;

/**
 * @author Eclipser
 */
public class NotificationFactoryLevel11 implements NotificationFactory
{
    private Context context;
    private final PendingIntent pendingIntent;

    public NotificationFactoryLevel11(Context context, PendingIntent pendingIntent)
    {
        this.context = context;
        this.pendingIntent = pendingIntent;
    }

    @Override
    public Notification getNotification(String title, String text, String ticker, String info)
    {
        Notification.Builder builder = new Notification.Builder(context);
        builder.setContentIntent(pendingIntent);
        builder.setContentTitle(title);
        builder.setContentText(text);
        builder.setContentInfo(info);
        builder.setTicker(ticker);
        builder.setOngoing(true);
        builder.setWhen(System.currentTimeMillis());
        builder.setSound(null);
        builder.setSmallIcon(R.drawable.notification);

        return builder.getNotification();
    }

}
