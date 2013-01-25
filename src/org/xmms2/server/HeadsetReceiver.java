package org.xmms2.server;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;

import java.util.HashSet;
import java.util.Set;

public class HeadsetReceiver extends BroadcastReceiver implements PlaybackStatusListener, AudioFocusListener
{
    private PlaybackStatus status = PlaybackStatus.STOPPED;
    private PlaybackStatus oldStatus = PlaybackStatus.STOPPED;

    private final Set<HeadsetListener> headsetListeners = new HashSet<HeadsetListener>();
    private HeadsetState state;
    private AudioFocusState audioFocusState;

    public HeadsetReceiver(HeadsetState state)
    {
        this.state = state;
    }

    @Override
    public void onReceive(Context context, Intent intent)
    {
        if (AudioManager.ACTION_AUDIO_BECOMING_NOISY.equals(intent.getAction())) {
            if (status == PlaybackStatus.PLAYING) {
                Server.pause();
            }

            state = HeadsetState.UNPLUGGED;
        } else if (Intent.ACTION_HEADSET_PLUG.equals(intent.getAction()) &&
                   intent.getExtras().getInt("state") == 1) {
            if (audioFocusState == AudioFocusState.FOCUSED && oldStatus == PlaybackStatus.PLAYING) {
                Server.play();
            }

            state = HeadsetState.PLUGGED;
        }

        for (HeadsetListener headsetListener : headsetListeners) {
            headsetListener.headsetStateChanged(state);
        }
    }

    @Override
    public void playbackStatusChanged(PlaybackStatus newStatus)
    {
        oldStatus = status;
        status = newStatus;
    }

    public void registerHeadsetListener(HeadsetListener listener)
    {
        listener.headsetStateChanged(state);
        headsetListeners.add(listener);
    }

    public void unregisterHeadsetListener(HeadsetListener listener)
    {
        headsetListeners.remove(listener);
    }

    @Override
    public void audioFocusChanged(AudioFocusState state)
    {
        audioFocusState = state;
    }
}
