package org.xmms2.server.plugins;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import org.xmms2.server.PlaybackStatusListener;
import org.xmms2.server.Server;

/**
 * @author Eclipser
 */
public class Output implements PlaybackStatusListener
{
    private AudioTrack audioTrack;
    private int bufferSize;
    private AudioManager audioManager;
    private final AudioManager.OnAudioFocusChangeListener audioFocusChangeListener;

    public Output(Server server)
    {
        this.audioManager = (AudioManager) server.getSystemService(Context.AUDIO_SERVICE);
        audioFocusChangeListener = server.getAudioFocusChangeListener();
        server.registerPlaybackListener(this);
    }

    public int getBufferSize()
    {
        return bufferSize;
    }

    public boolean open()
    {
        int ret = audioManager.requestAudioFocus(audioFocusChangeListener,
                                                 AudioManager.STREAM_MUSIC,
                                                 AudioManager.AUDIOFOCUS_GAIN);
        return ret == AudioManager.AUDIOFOCUS_REQUEST_GRANTED;
    }

    public void flush()
    {
        if (audioTrack != null) {
            audioTrack.flush();
        }
    }

    public void close()
    {
        if (audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.stop();
        }
        audioManager.abandonAudioFocus(audioFocusChangeListener);
    }

    public boolean write(byte[] buffer, int length)
    {
        if (audioTrack != null && audioTrack.getState() == AudioTrack.STATE_INITIALIZED
                               && audioTrack.getPlayState() != AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.play();
        }
        return audioTrack != null && audioTrack.write(buffer, 0, length) >= 0;
    }

    public boolean setFormat(int format, int channels, int rate)
    {
        int channelConfig = AudioFormat.CHANNEL_OUT_MONO;
        if (channels == 2) {
            channelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        }

        int formatConfig = AudioFormat.ENCODING_PCM_16BIT;
        if (format != 2) {
            return false;
        }

        try {
            int bufferSize = AudioTrack.getMinBufferSize(rate, channelConfig, formatConfig) * 10;
            audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, rate,
                                        channelConfig, formatConfig,
                                        bufferSize, AudioTrack.MODE_STREAM);

            this.bufferSize = bufferSize;
        } catch (IllegalArgumentException e) {
            return false;
        }

        return audioTrack.getState() == AudioTrack.STATE_INITIALIZED;
    }

    // Because the server doesn't tell "non-status API" output plugin if it's a pause, we'll listen to this here
    // and stop the audiotrack in case of pause.
    @Override
    public void playbackStatusChanged(int newStatus)
    {
        if (newStatus == 2 && audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.stop();
        }
    }
}
