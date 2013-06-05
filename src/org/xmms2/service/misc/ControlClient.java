package org.xmms2.service.misc;

import org.xmms2.eclipser.client.Client;
import org.xmms2.eclipser.client.ClientStatus;
import org.xmms2.eclipser.client.ClientStatusListener;
import org.xmms2.eclipser.client.commands.AbstractListener;
import org.xmms2.eclipser.client.commands.Playback;
import org.xmms2.eclipser.client.commands.Playlist;
import org.xmms2.eclipser.client.protocol.types.PlaybackStatus;

import java.io.IOException;
import java.net.URI;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Eclipser
 */
class ControlClient implements ClientStatusListener
{
    private final Client control;
    private final Set<PlaybackStatusListener> playbackStatusListeners = new HashSet<PlaybackStatusListener>();
    private PlaybackStatus status;

    ControlClient(URI address) throws IOException
    {
        control = new Client("controller", address);
        control.connectSync();
        status = control.executeSync(Playback.status()).response;

        AbstractListener <PlaybackStatus> statusListener = new AbstractListener<PlaybackStatus>()
        {
            @Override
            public void handleResponse(PlaybackStatus playbackStatus)
            {
                synchronized (playbackStatusListeners) {
                    status = playbackStatus;
                    for (PlaybackStatusListener playbackStatusListener : playbackStatusListeners) {
                        playbackStatusListener.playbackStatusChanged(status);
                    }
                }
            }
        };
        control.execute(Playback.statusBroadcast(), statusListener);
    }

    @Override
    public void clientStatusChanged(Client client, ClientStatus clientStatus)
    {
    }

    public void pause()
    {
        control.execute(Playback.pause(), null);
    }

    public void play()
    {
        control.execute(Playback.start(), null);

    }

    public void stop()
    {
        control.execute(Playback.stop(), null);

    }

    public void next()
    {
        control.execute(Playlist.setNextRelative(1L), null);
        control.execute(Playback.tickle(), null);
    }

    public void toggle()
    {
        if (status == PlaybackStatus.PLAY) {
            pause();
        } else {
            play();
        }
    }

    public void previous()
    {
        control.execute(Playlist.setNextRelative(-1L), null);
        control.execute(Playback.tickle(), null);
    }

    public void disconnect()
    {
        try {
            control.disconnect();
        } catch (IOException ignored) {}
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
}
