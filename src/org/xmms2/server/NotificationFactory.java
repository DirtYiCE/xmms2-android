package org.xmms2.server;

import android.app.Notification;

/**
 * @author Eclipser
 */
public interface NotificationFactory
{
    Notification getNotification(String title, String text, String ticker, String info);
}
