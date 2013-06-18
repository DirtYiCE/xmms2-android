package org.xmms2.service.medialib.updater;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import java.io.IOException;

/**
 * @author Eclipser
 */
public class UpdaterService extends Service
{
    private MediaLibraryUpdaterClient updaterClient;

    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        try {
            updaterClient = new MediaLibraryUpdaterClient("tcp://127.0.0.1:9667", this);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return START_STICKY;
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        updaterClient.disconnect();
    }
}
