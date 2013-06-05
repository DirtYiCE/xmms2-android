package org.xmms2.service.misc;

import android.text.TextUtils;
import org.xmms2.eclipser.client.commands.AbstractListener;
import org.xmms2.eclipser.client.protocol.types.Dict;
import org.xmms2.eclipser.client.protocol.types.Value;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Eclipser
 */
class MetadataHandler extends AbstractListener<Value>
{
    private String url;
    private String title;
    private String artist;
    private String pictureFront;

    private Set<MetadataListener> metadataListeners = new HashSet<MetadataListener>();

    @Override
    public void handleResponse(Value value)
    {
        if (value == null) return;

        Dict dict = value.getDict();
        String url = dict.getString("url");
        this.title = null;
        this.artist = null;
        this.pictureFront = null;

        try {
            this.url = new File(URLDecoder.decode(url, "UTF-8")).getName();
        } catch (UnsupportedEncodingException e) {
            this.url = url;
        }

        if (dict.containsKey("title")) {
            this.title = dict.getString("title");
        }
        if (dict.containsKey("artist")) {
            this.artist = dict.getString("artist");
        }
        if (dict.containsKey("picture_front")) {
            this.pictureFront = dict.getString("picture_front");
        }

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

    public String getCoverArtId()
    {
        return pictureFront;
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
