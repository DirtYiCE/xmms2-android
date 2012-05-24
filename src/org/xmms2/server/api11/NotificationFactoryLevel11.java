package org.xmms2.server.api11;

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import org.xmms2.server.NotificationFactory;
import org.xmms2.server.R;
import org.xmms2.server.ServiceTest;

/**
 * @author Eclipser
 */
public class NotificationFactoryLevel11 implements NotificationFactory
{
    private Context context;

    public NotificationFactoryLevel11(Context context)
    {
        this.context = context;
    }

    @Override
    public Notification create()
    {
        Notification.Builder builder = new Notification.Builder(context);
        builder.setContentIntent(PendingIntent.getActivity(context, 0, new Intent(context, ServiceTest.class), 0));
        builder.setContentText("Title");
        builder.setContentText("Text");
        builder.setContentInfo("Info");
        builder.setTicker("Ticker");
        builder.setOngoing(true);
        builder.setWhen(System.currentTimeMillis());
        builder.setSound(null);
        builder.setSmallIcon(R.drawable.notification);

        return builder.getNotification();
    }
}
