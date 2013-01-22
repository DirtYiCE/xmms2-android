package org.xmms2.server;

import java.util.HashSet;
import java.util.Set;

/**
 * @author Eclipser
 */
public class StatusHandler
{
    private PlaybackStatus status;
    private PlaybackStatus oldStatus;

    private final Set<PlaybackStatusListener> playbackStatusListeners = new HashSet<PlaybackStatusListener>();

    private void updateStatus(int status)
    {
        this.oldStatus = this.status;
        this.status = PlaybackStatus.get(status);

        for (PlaybackStatusListener playbackStatusListener : playbackStatusListeners) {
            playbackStatusListener.playbackStatusChanged(this.status);
        }

        /*
       */
    }

    public void registerPlaybackStatusListener(PlaybackStatusListener listener) {
        playbackStatusListeners.add(listener);
    }

    public void unregisterPlaybackStatusListener(PlaybackStatusListener listener) {
        playbackStatusListeners.remove(listener);
    }

    public PlaybackStatus getStatus()
    {
        return status;
    }

    public PlaybackStatus getOldStatus()
    {
        return oldStatus;
    }
}
