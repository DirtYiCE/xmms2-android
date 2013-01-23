package org.xmms2.server;

import android.app.Notification;

/**
 * @author Eclipser
 */
public interface NotificationUpdater
{
    void updateNotification(Notification notification);
    void removeNotification();
}
