package org.xmms2.server.api8;

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
public class NotificationFactoryLevel8 implements NotificationFactory
{
    private final Context context;

    public NotificationFactoryLevel8(Context context)
    {
        this.context = context;
    }

    @Override
    public Notification create()
    {
        Notification notification = new Notification(R.drawable.icon, "test", System.currentTimeMillis());
        notification.setLatestEventInfo(context, "Title", "Text",
                                        PendingIntent.getActivity(context, 0,
                                                                  new Intent(context, ServiceTest.class), 0));
        notification.sound = null;

        return notification;
    }
}
