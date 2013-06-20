package org.xmms2.service.misc;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
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
        notificationArt = decodeByteArray(bytes, notificationWidth, notificationHeight);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH) {
            final int ARTWORK_DEFAULT_SIZE = 256;
            Bitmap art = decodeByteArray(bytes, ARTWORK_DEFAULT_SIZE, ARTWORK_DEFAULT_SIZE);
            lockscreenArt = Bitmap.createBitmap(ARTWORK_DEFAULT_SIZE, ARTWORK_DEFAULT_SIZE, Bitmap.Config.ARGB_8888);
            lockscreenArt.setDensity(art.getDensity());
            Canvas canvas = new Canvas(lockscreenArt);
            float top = (ARTWORK_DEFAULT_SIZE - art.getHeight()) / 2;
            float left = (ARTWORK_DEFAULT_SIZE - art.getWidth()) / 2;
            canvas.drawBitmap(art, left, top, null);
        } else {
            lockscreenArt = null;
        }
    }

    private Bitmap decodeByteArray(byte[] bytes, int width, int height)
    {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inJustDecodeBounds = true;
        BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
        options.inSampleSize = calculateInSampleSize(options.outWidth, options.outHeight,
                                                     width, height);
        options.inJustDecodeBounds = false;
        return BitmapFactory.decodeByteArray(bytes, 0, bytes.length, options);
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
