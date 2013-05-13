package org.xmms2.server.plugins;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import org.xmms2.server.AudioFocusHandler;
import org.xmms2.server.PlaybackStatus;
import org.xmms2.server.PlaybackStatusListener;
import org.xmms2.server.Server;

import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * @author Eclipser
 */
public class Output implements PlaybackStatusListener, Runnable
{
    private static final int BUFFER_SIZE = 4096;
    private AudioTrack audioTrack;
    private int bufferSize;
    private AudioManager audioManager;
    private final AudioFocusHandler audioFocusChangeListener;
    private Thread audioThread = null;
    private boolean playing = false;

    private final Object lock = new Object();
    private int rate;
    private int channelConfig;
    private int formatConfig;
    private final AtomicBoolean formatChanged = new AtomicBoolean(false);
    private final AtomicBoolean paused = new AtomicBoolean(false);

    public Output(Server server)
    {
        this.audioManager = (AudioManager) server.getSystemService(Context.AUDIO_SERVICE);
        audioFocusChangeListener = new AudioFocusHandler(this);
        server.registerPlaybackListener(audioFocusChangeListener);
        server.registerHeadsetListener(audioFocusChangeListener);
        server.registerFocusListener(audioFocusChangeListener);
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
        audioFocusChangeListener.setFocus(ret == AudioManager.AUDIOFOCUS_REQUEST_GRANTED);
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
            audioThread.interrupt();
        }
        playing = false;
        free.clear();
        buffers.clear();
        audioManager.abandonAudioFocus(audioFocusChangeListener);
    }

    private final LinkedBlockingQueue<byte[]> free = new LinkedBlockingQueue<byte[]>(10);
    private final LinkedBlockingQueue<byte[]> buffers = new LinkedBlockingQueue<byte[]>(10);
    private byte[] a;
    private int bufpos = 0;
    private int latency = 0;

    public boolean write(byte[] buffer, int length)
    {
        try {
            if (audioThread == null || audioThread.isInterrupted() || !audioThread.isAlive()) {
                initAudioThread();
            }

            if (audioTrack == null && buffers.size() >= 3) {
                synchronized (buffers) {
                    buffers.notify();
                }
            }

            fillBuffer(buffer, length);

            return true;
        } catch (InterruptedException e) {
            return false;
        }
    }

    private boolean fillBuffer(byte[] buffer, int length) throws InterruptedException
    {
        int byteCount = Math.min(a.length - bufpos, length);
        System.arraycopy(buffer, 0, a, bufpos, byteCount);
        bufpos = bufpos + byteCount;

        if (bufpos == a.length) {
            buffers.put(a);
            updateLatency();
            bufpos = 0;
            a = free.poll();
            if (a == null) {
                a = new byte[BUFFER_SIZE];
            }

            if (byteCount < length) {
                System.arraycopy(buffer, byteCount, a, bufpos, length - byteCount);
                bufpos = length - byteCount;
            }
        }
        return false;
    }

    private void initAudioThread() throws InterruptedException
    {
        audioThread = new Thread(this, "XMMS2 Android Audio");
        playing = true;
        free.clear();
        while (free.remainingCapacity() > 0) {
            free.put(new byte[BUFFER_SIZE]);
        }
        a = free.take();
        audioThread.start();
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

        this.rate = rate;
        this.channelConfig = channelConfig;
        this.formatConfig = formatConfig;
        this.bufferSize = AudioTrack.getMinBufferSize(rate, channelConfig, formatConfig) * 10;

        synchronized (lock) {
            if (audioTrack != null && audioTrack.getPlayState() != AudioTrack.PLAYSTATE_STOPPED) {

                formatChanged.set(true);
                try {
                    if (bufpos > 0) { // put the last of the bytes belonging to the song in the play queue
                        byte[] b = new byte[bufpos];
                        System.arraycopy(a, 0, b, 0, bufpos);
                        bufpos = 0;
                        buffers.put(b);
                        a = free.take();
                    }

                    // wait for the audio thread to stop, it should since this is blocking any new buffers to come in
                    lock.wait();
                } catch (InterruptedException ignored) {}
            }
        }

        return true;
    }

    public void adjustVolume(float left, float right)
    {
        if (audioTrack != null && audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
            audioTrack.setStereoVolume(left, right);
        }
    }

    // Because the server doesn't tell "non-status API" output plugin if it's a pause, we'll listen to this here
    // and stop the audiotrack in case of pause.
    @Override
    public void playbackStatusChanged(PlaybackStatus newStatus)
    {
        if (newStatus == PlaybackStatus.PAUSED && audioTrack != null &&
            audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING && playing) {

            paused.set(true);
        } else if (newStatus == PlaybackStatus.PLAYING && audioTrack != null && playing) {
            paused.set(false);
            synchronized (lock) {
                lock.notify();
            }
        }
    }

    @Override
    public void run()
    {
        while (!audioThread.isInterrupted() && playing) {
            audioTrack = null;
            if (buffers.size() < 3) {
                synchronized (buffers) {
                    try {
                        buffers.wait();
                    } catch (InterruptedException ignored) {}
                }
            }

            audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC, rate,
                                       channelConfig, formatConfig,
                                       bufferSize, AudioTrack.MODE_STREAM);

            if (audioTrack.getState() == AudioTrack.STATE_INITIALIZED &&
                audioTrack.getPlayState() != AudioTrack.PLAYSTATE_PLAYING) {
                audioTrack.play();
            }

            try {
                playLoop();
            } catch (InterruptedException ignored) {}

            if (audioTrack != null && audioTrack.getState() == AudioTrack.STATE_INITIALIZED &&
                audioTrack.getPlayState() != AudioTrack.PLAYSTATE_STOPPED) {
                audioTrack.stop();
            }

            synchronized (lock) {
                lock.notify();
                formatChanged.set(false);
            }
        }
    }

    private void playLoop() throws InterruptedException
    {
        while (audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING &&
               !audioThread.isInterrupted()) {
            byte b[] = null;
            while (b == null) {
                if (paused.get()) {
                    audioTrack.pause();
                    synchronized (lock) {
                        lock.wait();
                    }
                    audioTrack.play();
                }
                b = buffers.poll(20, TimeUnit.MILLISECONDS);
                if (b == null && formatChanged.get()) {
                    return;
                }
            }

            updateLatency();

            if (audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
                audioTrack.write(b, 0, b.length);
            }
            if (b.length == BUFFER_SIZE) {
                free.offer(b);
            }
        }
    }

    // TODO inaccurate
    private void updateLatency()
    {
        latency = buffers.size() * BUFFER_SIZE + bufpos;
    }

}
