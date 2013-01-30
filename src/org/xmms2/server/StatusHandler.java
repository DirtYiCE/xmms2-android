package org.xmms2.server;

import java.util.HashSet;
import java.util.Set;

/**
 * @author Eclipser
 */
public class StatusHandler
{
    private PlaybackStatus status;

    private final Set<PlaybackStatusListener> playbackStatusListeners = new HashSet<PlaybackStatusListener>();

    private void updateStatus(int status)
    {
        this.status = PlaybackStatus.get(status);

        synchronized (playbackStatusListeners) {
            for (PlaybackStatusListener playbackStatusListener : playbackStatusListeners) {
                playbackStatusListener.playbackStatusChanged(this.status);
            }
        }
    }

    public void registerPlaybackStatusListener(PlaybackStatusListener listener) {
        synchronized (playbackStatusListeners) {
            playbackStatusListeners.add(listener);
        }
    }

    public void unregisterPlaybackStatusListener(PlaybackStatusListener listener) {
        synchronized (playbackStatusListeners) {
            playbackStatusListeners.remove(listener);
        }
    }

    public PlaybackStatus getStatus()
    {
        return status;
    }
}
