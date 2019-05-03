package com.example.brg_img;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;


import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import android.widget.TextView;

import android.graphics.Color;


public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("nativelib");
    }

    public native String stringFromJNI();
    int a = 1;
    int b = 2;

    public native String hwToConsole(int n1, int n2);
    public native int viewImage(int imgID);
    public native Bitmap openBitmap(Bitmap bitmap);

    String res = hwToConsole(a, b);

    private ImageView imageView;
    private Button button1;
    private Button button2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
//        TextView tv = findViewById(R.id.sample_text);

//        System.loadLibrary("nativelib");
//        nativelib nl = new nativelib();
//        String res = hwToConsole(a, b);


        this.imageView = (ImageView) this.findViewById(R.id.imageView);

        this.button1 = (Button) this.findViewById(R.id.button1);
        this.button2 = (Button) this.findViewById(R.id.button2);

        this.button1.setOnClickListener(new Button.OnClickListener() {

            @Override
            public void onClick(View v) {
                showImageOriginal();
            }
        });

        this.button2.setOnClickListener(new Button.OnClickListener() {

            @Override
            public void onClick(View v) {
                showImagePost();
            }
        });
    }

    private void showImageOriginal() {
        this.imageView.setImageResource(R.drawable.img);
    }

    private void showImagePost() {

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.img_res);
        Bitmap bm = openBitmap(bitmap);
        
        this.imageView.setImageBitmap(bm);


//        int id = viewImage(R.drawable.img_res);
//        this.imageView.setImageResource(id);
    }

}
