package org.xmms2.server;

import android.annotation.SuppressLint;
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
@SuppressLint("NewApi") // Care must be taken here, RemoteControlClient is API level 14+ only
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
        remoteControlClient.editMetadata(true)
                           .putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, logo).apply();
    }

    @Override
    public void playbackStatusChanged(PlaybackStatus newStatus)
    {
        if (!available) {
            return;
        }
        switch (newStatus) {
            case STOPPED:
                remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_STOPPED);
                break;
            case PLAYING:
                remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_PLAYING);
                break;
            case PAUSED:
                remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_PAUSED);
                break;
        }
    }

    @Override
    public void metadataChanged(MetadataHandler metadataHandler)
    {
        if (!available) {
            return;
        }
        RemoteControlClient.MetadataEditor metadataEditor = remoteControlClient.editMetadata(false);
        metadataEditor.putString(MediaMetadataRetriever.METADATA_KEY_ARTIST, metadataHandler.getArtist());
        metadataEditor.putString(MediaMetadataRetriever.METADATA_KEY_TITLE, metadataHandler.getTitle());
        // this somehow breaks stuff
//        Bitmap coverArt = metadataHandler.getCoverArt();
//        if (coverArt == null) {
//            coverArt = logo;
//        }
//        metadataEditor.putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, coverArt);
        metadataEditor.apply();
    }

    public void unregister()
    {
        if (!available) {
            return;
        }
        audioManager.unregisterRemoteControlClient(remoteControlClient);
    }
}
