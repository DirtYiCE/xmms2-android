package org.xmms2.service.misc;

import android.app.Notification;

/**
 * @author Eclipser
 */
public interface NotificationUpdater
{
    void updateNotification(Notification notification);
    void removeNotification();
}
