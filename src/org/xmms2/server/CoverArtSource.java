package org.xmms2.server;

import android.R;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v4.util.LruCache;

/**
 * @author Eclipser
 */
public class CoverArtSource extends LruCache<String, Bitmap>
{
    private final int notificationWidth;
    private final int notificationHeight;

    public CoverArtSource(Context context, int maxSize)
    {
        super(maxSize);

        Resources resources = context.getResources();
        notificationWidth = resources.getDimensionPixelSize(R.dimen.notification_large_icon_width);
        notificationHeight = resources.getDimensionPixelSize(R.dimen.notification_large_icon_height);
    }

    @Override
    protected int sizeOf(String key, Bitmap value)
    {
        return value.getByteCount();
    }

    @Override
    protected Bitmap create(String key)
    {
        byte[] buf = getBinData(key);
        if (buf == null) {
            return null;
        }

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeByteArray(buf, 0, buf.length, options);
        options.inSampleSize = calculateInSampleSize(options.outWidth, options.outHeight);
        options.inJustDecodeBounds = false;
        return BitmapFactory.decodeByteArray(buf, 0, buf.length, options);
    }

    private int calculateInSampleSize(int width, int height)
    {
        int inSampleSize = 1;

        if (width > notificationWidth || height > notificationHeight) {
            final int heightRatio = Math.round((float) height / (float) notificationHeight);
            final int widthRatio = Math.round((float) width / (float) notificationWidth);

            inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
        }

        return inSampleSize;
    }

    private native byte[] getBinData(String key);
}
