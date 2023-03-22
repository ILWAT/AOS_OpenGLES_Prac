package com.ilwat.firstnative;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.widget.TextView;


import com.ilwat.firstnative.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'firstnative' library on application startup.
    static {
        System.loadLibrary("firstnative");
    }

    private ActivityMainBinding binding;

    protected TutorialView graphicsView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
//        TextView tv = binding.sampleText;
//        tv.setText(stringFromJNI());

        graphicsView = new TutorialView(getApplication());
        setContentView(graphicsView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        graphicsView.onPause();

    }


    @Override
    protected void onResume()
    {
        super.onResume();
        graphicsView.onResume();
        return;
    }

    /**
     * A native method that is implemented by the 'firstnative' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}