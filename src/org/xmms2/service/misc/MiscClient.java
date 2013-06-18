package org.xmms2.service.misc;

import android.content.ComponentName;
import android.content.Context;
import android.media.AudioManager;
import org.xmms2.eclipser.client.Client;
import org.xmms2.eclipser.client.ClientStatus;
import org.xmms2.eclipser.client.ClientStatusListener;
import org.xmms2.eclipser.client.commands.AbstractListener;
import org.xmms2.eclipser.client.commands.Collection;
import org.xmms2.eclipser.client.commands.MediainfoReader;
import org.xmms2.eclipser.client.commands.Playback;
import org.xmms2.eclipser.client.protocol.fetchspecification.Aggregate;
import org.xmms2.eclipser.client.protocol.fetchspecification.FetchSpecification;
import org.xmms2.eclipser.client.protocol.fetchspecification.Get;
import org.xmms2.eclipser.client.protocol.fetchspecification.MetadataSpecification;
import org.xmms2.eclipser.client.protocol.types.collections.MediaList;

import java.io.IOException;
import java.net.URI;

/**
 * @author Eclipser
 */
public class MiscClient implements ClientStatusListener
{
    private static final MetadataSpecification FETCH_SPEC;

    static {
        FETCH_SPEC = FetchSpecification.metadata()
                                       .get(Get.FIELD, Get.VALUE)
                                       .fields("artist", "title", "url", "picture_front")
                                       .aggregate(Aggregate.FIRST);
    }

    private final Client client;
    private final NotificationHandler notificationHandler;
    private final MetadataHandler metadataHandler = new MetadataHandler();
    private final ControlClient control;
    private final ComponentName mediaButtonEventHandler;
    private final AudioManager audioManager;
    private final RemoteControl remoteControl;
    private final MediainfoReaderStatusSignalListener mediainfoReaderStatusSignalListener;

    public MiscClient(String uri, Context context,
                      NotificationUpdater notificationUpdater) throws IOException
    {
        URI address = URI.create(uri);
        client = new Client("metadata-updater", address);
        control = new ControlClient(address);
        client.connect(this);

        CoverArtSource coverArtSource = new CoverArtSource(client, context, 8 * 1024 * 1024);

        audioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
        mediaButtonEventHandler = new ComponentName(context, MediaButtonEventHandler.class);
        audioManager.registerMediaButtonEventReceiver(mediaButtonEventHandler);

        notificationHandler = new NotificationHandler(control, context, notificationUpdater, coverArtSource);
        metadataHandler.registerMetadataListener(notificationHandler);
        control.registerPlaybackStatusListener(notificationHandler);

        remoteControl = new RemoteControl(context, mediaButtonEventHandler, coverArtSource);
        metadataHandler.registerMetadataListener(remoteControl);
        control.registerPlaybackStatusListener(remoteControl);

        AbstractListener<Long> currentIdListener = new AbstractListener<Long>()
        {
            @Override
            public void handleResponse(Long id)
            {
                client.execute(Collection.query(MediaList.idList(id), FETCH_SPEC.build()), metadataHandler);
            }
        };

        client.execute(Playback.currentId(), currentIdListener);
        client.execute(Playback.currentIdBroadcast(), currentIdListener);

        mediainfoReaderStatusSignalListener = new MediainfoReaderStatusSignalListener(context);
        client.execute(MediainfoReader.statusBroadcast(), mediainfoReaderStatusSignalListener);
    }

    @Override
    public void clientStatusChanged(Client client, ClientStatus clientStatus)
    {
    }

    public void disconnect()
    {
        control.unregisterPlaybackStatusListener(notificationHandler);
        control.unregisterPlaybackStatusListener(remoteControl);
        metadataHandler.unregisterMetadataListener(notificationHandler);
        metadataHandler.unregisterMetadataListener(remoteControl);
        audioManager.unregisterMediaButtonEventReceiver(mediaButtonEventHandler);
        notificationHandler.unregister();
        remoteControl.unregister();
        control.disconnect();
        mediainfoReaderStatusSignalListener.removeNotification();
        try {
            client.disconnect();
        } catch (IOException ignored) {}
    }
}
