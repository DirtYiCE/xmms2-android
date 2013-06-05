package org.xmms2.service.misc;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Build;

/**
 * @author Eclipser
 */
class CoverArt
{
    final Bitmap notificationArt;
    final Bitmap lockscreenArt;

    CoverArt(byte[] bytes, int notificationWidth, int notificationHeight)
    {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
        options.inSampleSize = calculateInSampleSize(options.outWidth, options.outHeight,
                                                     notificationWidth, notificationHeight);
        options.inJustDecodeBounds = false;
        notificationArt = BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
            final int ARTWORK_DEFAULT_SIZE = 256;
            options.inSampleSize = calculateInSampleSize(options.outWidth, options.outHeight,
                                                         ARTWORK_DEFAULT_SIZE, ARTWORK_DEFAULT_SIZE);
            lockscreenArt = BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
        } else {
            lockscreenArt = null;
        }
    }

    int sizeOf()
    {
        int size = 0;
        if (lockscreenArt != null) {
            size += lockscreenArt.getRowBytes() * lockscreenArt.getHeight();
        }
        if (notificationArt != null) {
            size += notificationArt.getRowBytes() * notificationArt.getHeight();
        }
        return size;
    }

    private int calculateInSampleSize(int width, int height, int maxWidth, int maxHeight)
    {
        int inSampleSize = 1;

        if (width > maxWidth || height > maxHeight) {
            final int heightRatio = Math.round((float) height / (float) maxHeight);
            final int widthRatio = Math.round((float) width / (float) maxWidth);

            inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
        }

        return inSampleSize;
    }
}
