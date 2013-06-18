package org.xmms2.service.medialib.updater;

import android.util.Log;

import java.io.File;

/**
 * @author Eclipser
 */
class MediaObserver extends FileObserver
{
    interface EventListener {
        void created(File file);
        void deleted(File file);
        void changed(File file);
    }

    private final File observedPath;
    private final EventListener listener;

    MediaObserver(File path, EventListener listener)
    {
        super(path.getAbsolutePath(), ALL_EVENTS ^ ATTRIB ^ CLOSE_NOWRITE ^ OPEN);
        this.observedPath = path;
        this.listener = listener;
    }

    @Override
    public void onEvent(int event, int cookie, String path)
    {
        Log.d("FOO", "event " + event + " cookie " + cookie + " " + path);
    }
}
