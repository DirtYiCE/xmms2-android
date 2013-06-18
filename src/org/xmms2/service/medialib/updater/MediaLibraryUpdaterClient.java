package org.xmms2.service.medialib.updater;

import android.content.Context;
import android.os.Environment;
import org.xmms2.eclipser.client.Client;
import org.xmms2.eclipser.client.ClientStatus;
import org.xmms2.eclipser.client.ClientStatusListener;
import org.xmms2.eclipser.client.commands.Medialib;

import java.io.File;
import java.io.IOException;
import java.net.URI;

/**
 * @author Eclipser
 */
class MediaLibraryUpdaterClient implements ClientStatusListener, MediaObserver.EventListener
{
    private final Client client;
    private final MediaObserver observer;

    MediaLibraryUpdaterClient(String uri, Context context) throws IOException
    {
        client = new Client("mlib-updater", URI.create(uri));
        client.connect(this);

        observer = new MediaObserver(context.getExternalFilesDir(Environment.DIRECTORY_MUSIC), this);
        observer.startWatching();
    }

    @Override
    public void clientStatusChanged(Client client, ClientStatus clientStatus)
    {
    }

    @Override
    public void created(File file)
    {
        String path = String.format("file://%s", file.getAbsolutePath());
        if (file.isDirectory()) {
            client.execute(Medialib.importPath(path), null);
        } else {
            client.execute(Medialib.addEntry(path), null);
        }
    }

    @Override
    public void deleted(File file)
    {
    }

    @Override
    public void changed(File file)
    {
    }

    public void disconnect()
    {
        observer.stopWatching();
        try {
            client.disconnect();
        } catch (IOException ignored) {}
    }

}
