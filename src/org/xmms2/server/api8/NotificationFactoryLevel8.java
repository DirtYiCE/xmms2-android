package org.xmms2.server.api8;

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import org.w3c.dom.Text;
import org.xmms2.server.NotificationFactory;
import org.xmms2.server.R;
import org.xmms2.server.ServiceTest;

/**
 * @author Eclipser
 */
public class NotificationFactoryLevel8 implements NotificationFactory
{
    private final Context context;

    public NotificationFactoryLevel8(Context context)
    {
        this.context = context;
    }

    @Override
    public Notification getNotification(String title, String text, String ticker)
    {
        Notification notification = new Notification(R.drawable.notification, ticker, System.currentTimeMillis());
        notification.setLatestEventInfo(context, title, text,
                PendingIntent.getActivity(context, 0,
                        new Intent(context, ServiceTest.class), 0));
        notification.sound = null;

        return notification;
    }
}
