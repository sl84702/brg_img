package com.example.brg_img;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import java.io.*;


import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Bitmap.Config;
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

    public native byte[] changeImage(byte[] imageBytes);


    private ImageView imageView;
    private Button button1;
    private Button button2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


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

        ByteArrayOutputStream stream = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG, 100, stream);
        byte[] imageBytes = stream.toByteArray();


        byte[] newImageBytes = changeImage(imageBytes);

        InputStream inputStream = new ByteArrayInputStream(newImageBytes);
        BitmapFactory.Options o = new BitmapFactory.Options();
        Bitmap new_bitmap = BitmapFactory.decodeStream(inputStream, null, o);

        this.imageView.setImageBitmap(new_bitmap);

    }

}
