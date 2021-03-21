package com.example.parking;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnLogin = findViewById(R.id.btnLogin);
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(MainActivity.this, Search.class);
                startActivity(intent);
            }
        });


    }

    final String prefNameFirstStart = "firstAppStart";

    //check if first startup of application
    public boolean firstAppStart(){
        SharedPreferences preferences = getSharedPreferences(prefNameFirstStart, MODE_PRIVATE);

        if(preferences.getBoolean(prefNameFirstStart,true)){
            SharedPreferences.Editor editor = preferences.edit();
            editor.putBoolean(prefNameFirstStart, false);
            editor.commit();
            return true;
        }
        else {
            return false;
        }
    }



}