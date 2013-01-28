package org.xmms2.server;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.view.KeyEvent;

/**
 * @author Eclipser
 */
public class MediaButtonEventHandler extends BroadcastReceiver
{
    public void onReceive(Context context, Intent intent)
    {
        if (Intent.ACTION_MEDIA_BUTTON.equals(intent.getAction())) {
            KeyEvent event = (KeyEvent) intent.getParcelableExtra(Intent.EXTRA_KEY_EVENT);
            if (event.getAction() != KeyEvent.ACTION_DOWN) return;
            int keyCode = event.getKeyCode();
            if (KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE == keyCode) {
                Server.toggle();
            } else if (KeyEvent.KEYCODE_MEDIA_STOP == keyCode) {
                Server.stop();
            } else if (KeyEvent.KEYCODE_MEDIA_NEXT == keyCode) {
                Server.next();
            } else if (KeyEvent.KEYCODE_MEDIA_PREVIOUS == keyCode) {
                Server.previous();
            }
        }
    }
}
