package com.example.parking;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;

public class Search extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        ImageButton imgBtn = findViewById(R.id.imgBtn);
        imgBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();

            }
        });
    }

    final String databaseName ="level.db";
    final String databaseTableName = "level";
    //data consist of 7 days with intervals of 1 hour (how many places are used)
    //sun or rain
    //structure of data: day, hour, occupancy, weather
    //day: 0-6
    //hour: 0-23
    //occupancy: 0-240
    public void createDatabase(){
        SQLiteDatabase database = openOrCreateDatabase(databaseName, MODE_PRIVATE, null);
        database.execSQL("CREATE TABLE " + databaseTableName + " (day INTEGER, hour INTEGER, occupancy INTEGER, weather INTEGER)");

        database.execSQL("INSERT INTO "+ databaseTableName + " VALUES('0', '0', '13', '1')");
        database.execSQL("INSERT INTO "+ databaseTableName + " VALUES('0', '1', '14', '1')");

        database.close();
    }


    //user input
   // EditText editText=findViewById(R.id.editTextNumber);
   // String temp=String.valueOf(editText.getText());
   // int day = Integer.parseInt(temp);

    //EditText editText3=findViewById(R.id.editTextNumber3);
    //String temp3=String.valueOf(editText3.getText());
    //int hour = Integer.parseInt(temp3);



}