package com.serapina.marina;

import android.content.Intent;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

public class SecondActivity extends AppCompatActivity {
    Car[] cars;
    boolean[] choices;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        Intent intent = getIntent();
        cars = Car.getDefaultInstances();
        choices = intent.getBooleanArrayExtra("choices");
    }
}
