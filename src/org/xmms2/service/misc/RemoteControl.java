package org.xmms2.service.misc;

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
import android.text.TextUtils;
import org.xmms2.eclipser.client.protocol.types.PlaybackStatus;
import org.xmms2.server.R;

/**
 * @author Eclipser
 */
@SuppressLint("NewApi") // Care must be taken here, RemoteControlClient is API level 14+ only
class RemoteControl implements PlaybackStatusListener, MetadataListener, CoverArtListener
{

    private final RemoteControlClient remoteControlClient;
    private final AudioManager audioManager;
    private final boolean available;
    private final CoverArtSource coverArtSource;
    private final Context context;
    private String currentId = null;
    private boolean waitingForCover;

    RemoteControl(Context context, ComponentName mediaButtonEventHandler, CoverArtSource coverArtSource)
    {
        available = Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH;
        if (!available) {
            remoteControlClient = null;
            audioManager = null;
            this.context = null;
            this.coverArtSource = null;
            return;
        }

        this.context = context;
        this.coverArtSource = coverArtSource;
        coverArtSource.registerCoverArtListener(this);

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
        Bitmap logo = BitmapFactory.decodeResource(context.getResources(), R.drawable.logo);
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
            case STOP:
                remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_STOPPED);
                break;
            case PLAY:
                remoteControlClient.setPlaybackState(RemoteControlClient.PLAYSTATE_PLAYING);
                break;
            case PAUSE:
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
        updateCoverArt(metadataEditor, metadataHandler.getCoverArtId());
        metadataEditor.apply();
    }

    private void updateCoverArt(RemoteControlClient.MetadataEditor metadataEditor, String coverArtId)
    {
        if (TextUtils.equals(currentId, coverArtId) && !waitingForCover) {
            return;
        }

        waitingForCover = false;

        CoverArt coverArt = null;
        if (coverArtId != null) {
            coverArt = coverArtSource.get(coverArtId);
        }
        if (coverArt != null && coverArt.lockscreenArt != null) {
            Bitmap copy = coverArt.lockscreenArt.copy(coverArt.lockscreenArt.getConfig(), false);
            metadataEditor.putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, copy);
        } else {
            waitingForCover = coverArtId != null;
            if (currentId != null) {
                Bitmap logo = BitmapFactory.decodeResource(context.getResources(), R.drawable.logo);
                metadataEditor.putBitmap(RemoteControlClient.MetadataEditor.BITMAP_KEY_ARTWORK, logo);
            }
        }

        currentId = coverArtId;
    }

    public void unregister()
    {
        if (!available) {
            return;
        }
        coverArtSource.unregisterCoverArtListener(this);
        audioManager.unregisterRemoteControlClient(remoteControlClient);
    }

    @Override
    public void artAvailable(String key)
    {
        RemoteControlClient.MetadataEditor metadataEditor = remoteControlClient.editMetadata(false);
        updateCoverArt(metadataEditor, key);
        metadataEditor.apply();
    }
}
