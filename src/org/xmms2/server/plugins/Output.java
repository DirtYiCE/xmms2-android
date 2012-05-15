package org.xmms2.server.plugins;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

/**
 * @author Eclipser
 */
public class Output
{
    private AudioTrack audioTrack;
    private int bufferSize;

    public int getBufferSize()
    {
        return bufferSize;
    }

    public boolean open()
    {
//        if (audioTrack == null) {
//            return false;
//        }
//
//        try {
//            audioTrack.play();
//        } catch (IllegalStateException e) {
//            return false;
//        }
        return true;
    }

    public void flush()
    {
        if (audioTrack != null) {
            audioTrack.flush();
        }
    }

    public void close()
    {
        if (audioTrack != null) {
            audioTrack.stop();
        }
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

        return true;
    }
}
