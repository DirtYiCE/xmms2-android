package org.xmms2.service.misc;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.view.KeyEvent;

import java.io.IOException;
import java.net.URI;

/**
 * @author Eclipser
 */
public class MediaButtonEventHandler extends BroadcastReceiver
{
    private final ControlClient control;

    public MediaButtonEventHandler()
    {
        ControlClient ctrl = null;
        try {
            ctrl = new ControlClient(URI.create("tcp://localhost:9667"));
        } catch (IOException ignored) {}

        control = ctrl;
    }

    public void onReceive(Context context, Intent intent)
    {
        if (Intent.ACTION_MEDIA_BUTTON.equals(intent.getAction())) {
            KeyEvent event = intent.getParcelableExtra(Intent.EXTRA_KEY_EVENT);
            if (event.getAction() != KeyEvent.ACTION_DOWN || control == null) return;
            int keyCode = event.getKeyCode();
            if (KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE == keyCode) {
                control.toggle();
            } else if (KeyEvent.KEYCODE_MEDIA_STOP == keyCode) {
                control.stop();
            } else if (KeyEvent.KEYCODE_MEDIA_NEXT == keyCode) {
                control.next();
            } else if (KeyEvent.KEYCODE_MEDIA_PREVIOUS == keyCode) {
                control.previous();
            }
            control.disconnect();
        }
    }
}
