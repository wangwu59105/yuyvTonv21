package com.sf.nv.utils;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    Yuyv yuyv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        yuyv = new Yuyv();
        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(yuyv.stringFromJNI());

        tvClick(tv);
    }

    private void tvClick(TextView tv) {

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                run();
            }
        });
    }


    private void run() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                int i = 0;
                int with = 640;
                int height = 480;
                int yuyvSize = with * height * 2;
                int nv21Size = with * height * 3 / 2;
                byte[] yuy2 = new byte[yuyvSize];
                for (int m = 0; m < yuyvSize; m++) {
                    yuy2[m] = (byte) ((m%2==0)?1:0);
                }
                long time = System.currentTimeMillis();
                byte[] nv21 = new byte[nv21Size];
                yuyv.YuyvToNv21(yuy2, with, height,nv21);
                Log.e("yuyv",nv21[0]+"" );
            }
        }).start();
    }
}
