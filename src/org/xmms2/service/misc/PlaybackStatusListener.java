package org.xmms2.service.misc;


import org.xmms2.eclipser.client.protocol.types.PlaybackStatus;

/**
 * @author Eclipser
 */
interface PlaybackStatusListener
{
    void playbackStatusChanged(PlaybackStatus newStatus);
}
