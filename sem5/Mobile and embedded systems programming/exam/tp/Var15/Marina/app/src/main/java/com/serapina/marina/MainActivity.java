package com.serapina.marina;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity
{
    Button showCheckedButton;
    ListView carsList;

    private Car[] cars;
    private boolean[] choices;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        showCheckedButton = (Button) findViewById(R.id.show_checked);
        carsList = (ListView) findViewById(R.id.list_view);

        cars = Car.getDefaultInstances();
        String[] carsStr = new String[cars.length];
        choices = new boolean[cars.length];
        
        for(int i = 0; i < cars.length; ++i)
            choices[i] = false;

        for(int i = 0; i < cars.length; ++i)
        {
            carsStr[i] = cars[i].model;
        }

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_multiple_choice, carsStr);

        carsList.setAdapter(adapter);
        carsList.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);

        carsList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                choices[position] = !choices[position];
            }
        });
        showCheckedButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, SecondActivity.class);
                intent.putExtra("choices", choices);
                startActivity(intent);
            }
        });
    }
}