package org.xmms2.service.misc;

import android.content.Context;
import android.content.res.Resources;
import android.support.v4.util.LruCache;
import org.xmms2.eclipser.client.Client;
import org.xmms2.eclipser.client.commands.AbstractListener;
import org.xmms2.eclipser.client.commands.Bindata;

import java.util.*;

/**
 * @author Eclipser
 */
class CoverArtSource extends LruCache<String, CoverArt>
{
    private final int notificationWidth;
    private final int notificationHeight;
    private final Client client;
    private final Set<CoverArtListener> coverArtListeners;
    private final Map<String, DataListener> listenerMap;

    CoverArtSource(Client client, Context context, int maxSize)
    {
        super(maxSize);
        this.client = client;

        Resources resources = context.getResources();
        notificationWidth = resources.getDimensionPixelSize(android.R.dimen.notification_large_icon_width);
        notificationHeight = resources.getDimensionPixelSize(android.R.dimen.notification_large_icon_height);
        coverArtListeners = Collections.synchronizedSet(new HashSet<CoverArtListener>());
        listenerMap = Collections.synchronizedMap(new HashMap<String, DataListener>());
    }

    @Override
    protected int sizeOf(String key, CoverArt value)
    {
        return value.sizeOf();
    }

    @Override
    protected CoverArt create(String key)
    {
        if (!listenerMap.containsKey(key)) {
            DataListener listener = new DataListener(key);
            listenerMap.put(key, listener);
            client.execute(Bindata.retrieve(key), listener);
        }
        return null;
    }

    private class DataListener extends AbstractListener<byte[]>
    {
        private final String key;

        public DataListener(String key)
        {
            this.key = key;
        }

        @Override
        public void handleResponse(byte[] bytes)
        {
            CoverArt coverArt = new CoverArt(bytes, notificationWidth, notificationHeight);
            put(key, coverArt);
            notifyListeners(key);
            listenerMap.remove(key);
        }
    }

    private void notifyListeners(final String key)
    {
        for (CoverArtListener coverArtListener : coverArtListeners) {
            coverArtListener.artAvailable(key);
        }
    }

    public void registerCoverArtListener(CoverArtListener coverArtListener)
    {
        coverArtListeners.add(coverArtListener);
    }

    public void unregisterCoverArtListener(CoverArtListener coverArtListener)
    {
        coverArtListeners.remove(coverArtListener);
    }
}
