package org.xmms2.server;

import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.AudioManager;
import android.media.MediaMetadataRetriever;
import android.media.RemoteControlClient;
import android.os.Build;

/**
 * @author Eclipser
 */
public class RemoteControl implements PlaybackStatusListener, MetadataListener
{

    private final RemoteControlClient remoteControlClient;
    private final AudioManager audioManager;
    private final Bitmap logo;
    private final boolean available;

    public RemoteControl(Context context, ComponentName mediaButtonEventHandler)
    {
        available = Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH;
        if (!available) {
            remoteControlClient = null;
            audioManager = null;
            logo = null;
            return;
        }

        audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        Intent mediaButtonIntent = new Intent(Intent.ACTION_MEDIA_BUTTON);
        mediaButtonIntent.setComponent(mediaButtonEventHandler);
        PendingIntent mediaPendingIntent = PendingIntent.getBroadcast(context, 0, mediaButtonIntent, 0);
        remoteControlClient = new RemoteControlClient(mediaPendingIntent);
        remoteControlClient.setTransportControlFlags(RemoteControlClient.FLAG_KEY_MEDIA_NEXT |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_PREVIOUS |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_PLAY_PAUSE |
                                                     RemoteControlClient.FLAG_KEY_MEDIA_STOP);
        audioManager.registerRemoteControlClient(remoteControlClient);
        logo = BitmapFactory.decodeResource(context.getResources(), R.drawable.logo);
        remoteControlClient.editMetadata(true).putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, logo).apply();
    }

    @Override
    public void playbackStatusChanged(PlaybackStatus newStatus)
    {
        if (!available) {
            return;
        }
        if (newStatus == PlaybackStatus.STOPPED) {
            remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_STOPPED);
        } else {
            remoteControlClient.setPlaybackState(newStatus == PlaybackStatus.PLAYING ? RemoteControlClient.PLAYSTATE_PLAYING : RemoteControlClient.PLAYSTATE_PAUSED);
        }
    }

    @Override
    public void metadataChanged(MetadataHandler metadataHandler)
    {
        if (!available) {
            return;
        }
        remoteControlClient.editMetadata(false)
                           .putString(MediaMetadataRetriever.METADATA_KEY_ARTIST, metadataHandler.getArtist())
                           .putString(MediaMetadataRetriever.METADATA_KEY_TITLE, metadataHandler.getTitle()).apply();
    }

    public void unregister()
    {
        if (!available) {
            return;
        }
        audioManager.unregisterRemoteControlClient(remoteControlClient);
    }
}
