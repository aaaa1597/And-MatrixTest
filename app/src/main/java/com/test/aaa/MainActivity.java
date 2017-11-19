package com.test.aaa;

import android.app.Activity;
import android.graphics.Matrix;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Matrix mtx = new Matrix();
        mtx.reset();
//        mtx.postTranslate(-2,-2);
//        mtx.postTranslate(-100,-100);
        mtx.postTranslate(-100,-100);
        String log001 = mtx.toString();
        Log.d("aaaaa", log001);

        mtx.postScale(10,10);
        String log002 = mtx.toString();
        Log.d("aaaaa", log002);

//        mtx.postTranslate(2,2);
//        mtx.postTranslate(100,100);
        mtx.postTranslate(100,100);
        String log003 = mtx.toString();
        Log.d("aaaaa", log003);

        float[] pts = new float[12];
        pts[0] = 0;    pts[1] = 0;
        pts[2] = 4096; pts[3] = 4096;
        pts[4] = 6144; pts[5] = 6144;
        pts[6] = 100;  pts[7] = 100;
        pts[8] = 8192; pts[9] = 8192;
        pts[10]= 12288;pts[11]= 12288;
        mtx.mapPoints(pts);
        String log004 = pts.toString();
        Log.d("aaaaa", log004);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}
