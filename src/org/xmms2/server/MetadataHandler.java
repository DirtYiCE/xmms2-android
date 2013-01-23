package org.xmms2.server;

import android.text.TextUtils;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Eclipser
 */
public class MetadataHandler
{

    private String url;
    private String title;
    private String artist;

    private Set<MetadataListener> metadataListeners = new HashSet<MetadataListener>();

    private void setCurrentlyPlayingInfo(String url, String artist, String title)
    {
        try {
            this.url = new File(URLDecoder.decode(url, "UTF-8")).getName();
        } catch (UnsupportedEncodingException e) {
            this.url = url;
        }
        this.title = title;
        this.artist = artist;

        for (MetadataListener metadataListener : metadataListeners) {
            metadataListener.metadataChanged(this);
        }
    }

    public String getTitle()
    {
        return !TextUtils.isEmpty(title) ? title : url;
    }

    public String getArtist()
    {
        return artist != null ? artist : "";
    }

    public String getTicker()
    {
        if (artist == null && title == null) {
            return url;
        } else if (artist == null) {
            return title;
        } else if (title == null) {
            return artist;
        }
        return String.format("%s - %s", artist, title);
    }

    public void registerMetadataListener(MetadataListener listener)
    {
        metadataListeners.add(listener);
    }

    public void unregisterMetadataListener(MetadataListener listener)
    {
        metadataListeners.remove(listener);
    }
}
