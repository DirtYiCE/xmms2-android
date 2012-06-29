package org.xmms2.server.plugins;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import org.xmms2.server.PlaybackStatusListener;
import org.xmms2.server.Server;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author Eclipser
 */
public class Output implements PlaybackStatusListener, Runnable
{
    private AudioTrack audioTrack;
    private int bufferSize;
    private AudioManager audioManager;
    private final AudioManager.OnAudioFocusChangeListener audioFocusChangeListener;
    private Thread audioThread = null;
    private boolean playing = false;
    private ArrayList<byte[]> pausedBuffers = new ArrayList<byte[]>();

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
        buffers.clear();
        if (audioTrack != null) {
            audioTrack.flush();
        }
    }

    public void close()
    {
        if (audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.stop();
            playing = false;
            buffers.clear();
            pausedBuffers.clear();
            audioThread.interrupt();
        }
        audioManager.abandonAudioFocus(audioFocusChangeListener);
    }

    private final LinkedBlockingQueue<byte[]> buffers = new LinkedBlockingQueue<byte[]>(10);
    private ByteBuffer a = ByteBuffer.allocate(4096);

    public boolean write(byte[] buffer, int length)
    {
        if (audioThread == null || audioThread.isInterrupted() || !audioThread.isAlive()) {
            audioThread = new Thread(this, "XMMS2 Android Audio");
            playing = true;
            if (!pausedBuffers.isEmpty()) {
                buffers.addAll(pausedBuffers);
                pausedBuffers.clear();
            }
            audioThread.start();
        }

        if (buffers.size() >= 3) {
            synchronized (buffers) {
                buffers.notify();
            }
        }

        int byteCount = Math.min(a.remaining(), length);
        a.put(buffer, 0, byteCount);

        if (!a.hasRemaining()) {
            try {
                buffers.put(a.array());
            } catch (InterruptedException e) {
                return false;
            }
            a = ByteBuffer.allocate(4096);

            if (byteCount < length) {
                a.put(buffer, byteCount, length - byteCount);
            }
        }

        return audioThread.isAlive();
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
        if (newStatus == 2 && audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING && playing) {
            buffers.drainTo(pausedBuffers);
            buffers.clear();
            audioTrack.stop();
        }
    }

    @Override
    public void run()
    {
        if (buffers.size() < 3) {
            synchronized (buffers) {
                try {
                    buffers.wait();
                } catch (InterruptedException ignored) {}
            }
        }

        if (audioTrack != null && audioTrack.getState() == AudioTrack.STATE_INITIALIZED
                && audioTrack.getPlayState() != AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.play();
        }

        while (audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
            byte b[];
            try {
                b = buffers.take();
            } catch (InterruptedException e) {
                break;
            }
            if (audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
                audioTrack.write(b, 0, b.length);
            }
        }
    }
}
