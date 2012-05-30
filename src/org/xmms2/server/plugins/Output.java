package org.xmms2.server.plugins;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

/**
 * @author Eclipser
 */
public class Output implements AudioManager.OnAudioFocusChangeListener
{
    private AudioTrack audioTrack;
    private int bufferSize;
    private AudioManager audioManager;

    public Output(Context context)
    {
        this.audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
    }

    public int getBufferSize()
    {
        return bufferSize;
    }

    public boolean open()
    {
        int ret = audioManager.requestAudioFocus(this, AudioManager.STREAM_MUSIC, AudioManager.AUDIOFOCUS_GAIN);
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
        audioManager.abandonAudioFocus(this);
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

    @Override
    public void onAudioFocusChange(int focusChange)
    {
        if (focusChange == AudioManager.AUDIOFOCUS_GAIN) {
           Log.d("XMMS2 Output", "Focus gained");
        } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS) {
            Log.d("XMMS2 Output", "Focus lost");
        } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT) {
            Log.d("XMMS2 Output", "Focus loss transient");
        } else if (focusChange == AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK) {
            Log.d("XMMS2 Output", "Focus loss transient can duck");
        }
    }
}
