package org.ripreal.androidutils;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        MainApp mainApp = new MainApp(this, 0);
        mainApp.show();
        mainApp.startScreenWatch();
    }

    public void loadLibOnClick(View view) {
        // Used to load the 'native-lib' library on application startup.
        System.loadLibrary("org_ripreal_androidutils");
        MainApp mainApp = new MainApp(this, 0);
        mainApp.testScreenActions();
    }
}
