package org.xmms2.service.misc;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v4.app.NotificationCompat;
import android.text.TextUtils;
import android.widget.RemoteViews;
import org.xmms2.eclipser.client.protocol.types.PlaybackStatus;
import org.xmms2.server.R;
import org.xmms2.server.Server;

/**
 * @author Eclipser
 */
class NotificationHandler implements PlaybackStatusListener, MetadataListener, CoverArtListener
{
    private static final String ACTION_TOGGLE_PLAYBACK = "org.xmms2.server.action.TOGGLE_PLAYBACK";
    private static final String ACTION_NEXT = "org.xmms2.server.action.NEXT";
    private static final String ACTION_STOP_PLAYBACK = "org.xmms2.server.action.STOP_PLAYBACK";

    private final Context context;
    private final RemoteViews notificationView;
    private final ControlClient control;
    private final NotificationUpdater updater;
    private final CoverArtSource coverArtSource;
    private final NotificationCompat.Builder builder;

    private String coverArtId;
    private boolean waitingForCover;

    private final BroadcastReceiver notificationActionReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            if (ACTION_TOGGLE_PLAYBACK.equals(intent.getAction())) {
                control.toggle();
            } else if (ACTION_STOP_PLAYBACK.equals(intent.getAction())) {
                control.stop();
            } else if (ACTION_NEXT.equals(intent.getAction())) {
                control.next();
            }
        }
    };

    NotificationHandler(ControlClient control, Context context, NotificationUpdater updater,
                        CoverArtSource coverArtSource)
    {
        this.control = control;
        this.updater = updater;
        this.coverArtSource = coverArtSource;
        this.context = context.getApplicationContext();
        Intent intent = new Intent(Server.ACTION_START_CLIENT);
        intent.putExtra("address", "tcp://localhost:9667");
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        PendingIntent clientStartIntent = PendingIntent.getActivity(this.context, 0, intent, 0);

        notificationView = new RemoteViews(this.context.getPackageName(), R.layout.notification);
        Intent toggle = new Intent(ACTION_TOGGLE_PLAYBACK);
        notificationView.setOnClickPendingIntent(R.id.toggle, PendingIntent.getBroadcast(this.context, 0, toggle, 0));

        Intent next = new Intent(ACTION_NEXT);
        notificationView.setOnClickPendingIntent(R.id.next, PendingIntent.getBroadcast(this.context, 0, next, 0));

        Intent stop = new Intent(ACTION_STOP_PLAYBACK);
        notificationView.setOnClickPendingIntent(R.id.close, PendingIntent.getBroadcast(this.context, 0, stop, 0));

        IntentFilter notificationActionFilter = new IntentFilter();
        notificationActionFilter.addAction(ACTION_TOGGLE_PLAYBACK);
        notificationActionFilter.addAction(ACTION_NEXT);
        notificationActionFilter.addAction(ACTION_STOP_PLAYBACK);
        this.context.registerReceiver(notificationActionReceiver, notificationActionFilter);

        builder = new NotificationCompat.Builder(this.context);
        builder.setContentIntent(clientStartIntent);
        builder.setContent(notificationView);
        builder.setOngoing(true);
        builder.setSound(null);
        builder.setSmallIcon(R.drawable.notification);

        coverArtSource.registerCoverArtListener(this);
    }

    @Override
    public void metadataChanged(MetadataHandler metadataHandler)
    {
        builder.setContentTitle(metadataHandler.getTitle());
        notificationView.setTextViewText(R.id.title, metadataHandler.getTitle());
        builder.setContentText(metadataHandler.getArtist());
        notificationView.setTextViewText(R.id.artist, metadataHandler.getArtist());
        builder.setTicker(metadataHandler.getTicker());
        setCoverArt(metadataHandler.getCoverArtId());

        updater.updateNotification(builder.build());
    }

    private void setCoverArt(String id)
    {
        if (TextUtils.equals(id, coverArtId) && !waitingForCover) {
            return;
        }

        waitingForCover = false;

        CoverArt coverArt = null;
        if (id != null) {
            coverArt = coverArtSource.get(id);
        }
        if (coverArt != null) {
            builder.setLargeIcon(coverArt.notificationArt);
            notificationView.setImageViewBitmap(R.id.icon, coverArt.notificationArt);
        } else {
            waitingForCover = id != null;
            builder.setLargeIcon(null);
            notificationView.setImageViewResource(R.id.icon, R.drawable.notification);
        }

        coverArtId = id;
    }

    @Override
    public void playbackStatusChanged(PlaybackStatus newStatus)
    {
        if (newStatus != PlaybackStatus.STOP) {
            int srcId = newStatus == PlaybackStatus.PLAY ? R.drawable.pause : R.drawable.play;
            notificationView.setImageViewResource(R.id.toggle, srcId);
            int id = newStatus == PlaybackStatus.PLAY ? R.string.playing : R.string.pause;
            builder.setContentInfo(context.getString(id));

            updater.updateNotification(builder.build());
        } else {
            updater.removeNotification();
        }
    }

    public void unregister()
    {
        context.unregisterReceiver(notificationActionReceiver);
        coverArtSource.unregisterCoverArtListener(this);
    }

    @Override
    public void artAvailable(String key)
    {
        setCoverArt(key);
        updater.updateNotification(builder.build());
    }
}
