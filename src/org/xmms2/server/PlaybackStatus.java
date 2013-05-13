package org.xmms2.server;

import android.content.res.Resources;
import android.util.SparseArray;

/**
 * @author Eclipser
 */
public enum PlaybackStatus
{
    STOPPED(0, R.string.stopped),
    PLAYING(1, R.string.playing),
    PAUSED(2, R.string.paused);
    private final int id;
    private final int resource;
    private static final SparseArray<PlaybackStatus> map = new SparseArray<PlaybackStatus>();

    private PlaybackStatus(int id, int resource)
    {
        this.id = id;
        this.resource = resource;
    }

    static {
        for (PlaybackStatus t : PlaybackStatus.class.getEnumConstants()) {
            map.put(t.id, t);
        }
    }

    public static PlaybackStatus get(int status) {
        return map.get(status);
    }

    public String getLiteralString(Resources resources)
    {
        return resources.getString(resource);
    }
}
