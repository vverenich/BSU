package com.example.pmvs_lab_8_3_1;

import android.os.Bundle;
import android.app.Activity;

import androidx.core.view.*;

import android.view.*;
import android.widget.*;
import android.widget.RelativeLayout;

public class MainActivity extends Activity implements GestureDetector.OnGestureListener,
        GestureDetector.OnDoubleTapListener {
    private GestureDetectorCompat mDetector;
    public RelativeLayout relativeLayout;
    private TextView tvOut;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mDetector = new GestureDetectorCompat(this, this);
        mDetector.setOnDoubleTapListener(this);
        tvOut = (TextView) findViewById(R.id.TextView1);
        relativeLayout = (RelativeLayout) findViewById(R.id.relativelayout);
        relativeLayout.setBackgroundResource(R.color.black);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        this.mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    @Override
    public boolean onDown(MotionEvent event) {
        tvOut.setText("onDown");
        return false;
    }

    @Override
    public boolean onFling(MotionEvent event1, MotionEvent event2,
                           float velocityX, float velocityY) {
        tvOut.setText("onFling");
        relativeLayout.setBackgroundResource(R.color.purple);
        return true;
    }

    @Override
    public void onLongPress(MotionEvent event) {
        tvOut.setText("onLongPress");
        relativeLayout.setBackgroundResource(R.color.dark_blue);
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,
                            float distanceY) {
        tvOut.setText("onScroll");
        relativeLayout.setBackgroundResource(R.color.light_blue);
        return true;
    }

    @Override
    public void onShowPress(MotionEvent event) {
        tvOut.setText("onShowPress");
        relativeLayout.setBackgroundResource(R.color.green);
    }

    @Override
    public boolean onSingleTapUp(MotionEvent event) {
        tvOut.setText("onSingleTapUp");
        relativeLayout.setBackgroundResource(R.color.yellow);
        return true;
    }

    @Override
    public boolean onDoubleTap(MotionEvent event) {
        tvOut.setText("onDoubleTap");
        relativeLayout.setBackgroundResource(R.color.orange);
        return true;
    }

    @Override
    public boolean onDoubleTapEvent(MotionEvent event) {
        tvOut.setText("onDoubleTapEvent");
        return true;
    }

    @Override
    public boolean onSingleTapConfirmed(MotionEvent event) {
        tvOut.setText("onSingleTapConfirmed");
        relativeLayout.setBackgroundResource(R.color.red);
        return true;
    }
}