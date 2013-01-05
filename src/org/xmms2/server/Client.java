package org.xmms2.server;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;

/**
 * @author Eclipser
 */
public class Client extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        try {
            startActivity(new Intent(Server.ACTION_START_CLIENT));
            finish();
        } catch (ActivityNotFoundException ignored) {}

        setContentView(R.layout.main);
    }

    public void goToStore(View v)
    {
        Intent intent = new Intent(Intent.ACTION_VIEW);
        intent.setData(Uri.parse("market://search?q=xmms2%20client"));
        startActivity(intent);
        finish();
    }
}
