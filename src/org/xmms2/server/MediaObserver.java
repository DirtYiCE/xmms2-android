package org.xmms2.server;

import android.os.FileObserver;

/**
 * @author Eclipser
 */
public class MediaObserver extends FileObserver
{
    private native void check(String path);

    public MediaObserver(String path)
    {
        super(path, FileObserver.CREATE | FileObserver.DELETE);
    }

    @Override
    public void onEvent(int event, String path)
    {
        check(path);
    }
}
