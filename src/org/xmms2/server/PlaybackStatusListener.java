package org.xmms2.server;

/**
 * @author Eclipser
 */
public interface PlaybackStatusListener
{
    void adjustVolume(float left, float right);
    void playbackStatusChanged(int newStatus);
}
