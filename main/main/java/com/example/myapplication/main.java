package com.example.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.sql.SQLOutput;
import java.util.Scanner;
import java.util.Set;
import java.util.UUID;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;


import android.os.Bundle;
import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class main extends Activity {
    RelativeLayout layout_joystick;
    ImageView image_joystick, image_border;
    TextView textView1, textView2, textView3, textView4, textView5;
    Button on_button;
    Button off_button;
    TextView speed;
    Scanner scanner;
    Switch go_auto;

    joystickClass js;

    private final String DEVICE_ADDRESS = "20:16:12:14:71:18"; //MAC Address of Bluetooth Module
    private final UUID PORT_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    private BluetoothDevice device;
    private BluetoothSocket socket;
    private OutputStream outputStream;
    private InputStream inputStream;
    Button bluetooth_connect_button;
    String command;
    private byte[] reader;
    String string;


    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

         final TextView reading = (TextView) findViewById(R.id.reading);
        SeekBar seekBar = (SeekBar) findViewById(R.id.seekBar);
        seekBar.setMax(5);
        textView1 = (TextView)findViewById(R.id.textView1);
        textView2 = (TextView)findViewById(R.id.textView2);
        textView3 = (TextView)findViewById(R.id.textView3);
        textView4 = (TextView)findViewById(R.id.textView4);
        textView5 = (TextView)findViewById(R.id.textView5);
        bluetooth_connect_button = (Button) findViewById(R.id.bluetooth_connect_btn);
        on_button = (Button)findViewById(R.id.on_button);
        off_button = (Button)findViewById(R.id.off_button);
        speed =  findViewById(R.id.speed);
        go_auto = (Switch) findViewById(R.id.go_auto);

        layout_joystick = (RelativeLayout)findViewById(R.id.layout_joystick);

        js = new joystickClass(getApplicationContext()
                , layout_joystick, R.drawable.image_button);
        js.setStickSize(150, 150);
        js.setLayoutSize(500, 500);
        js.setLayoutAlpha(150);
        js.setStickAlpha(100);
        js.setOffset(90);
        js.setMinimumDistance(50);

        layout_joystick.setOnTouchListener(new OnTouchListener() {
            public boolean onTouch(View arg0, MotionEvent arg1) {

                js.drawStick(arg1);
                if(arg1.getAction() == MotionEvent.ACTION_DOWN
                        || arg1.getAction() == MotionEvent.ACTION_MOVE) {
                    textView1.setText("X : " + String.valueOf(js.getX()));
                    textView2.setText("Y : " + String.valueOf(js.getY()));
                    textView3.setText("Angle : " + String.valueOf(js.getAngle()));
                    textView4.setText("Distance : " + String.valueOf(js.getDistance()));

                    int direction = js.get8Direction();
                    switch (direction) {

                    case joystickClass.STICK_UP: 
                        textView5.setText("Direction : Up");
                        command = "w";
                        break;
                    case joystickClass.STICK_UPRIGHT: 
                        textView5.setText("Direction : Up Right");
                        command = "e";
                        break;
                    case joystickClass.STICK_RIGHT: 
                        textView5.setText("Direction : Right");
                        command = "d";
                        break;
                    case joystickClass.STICK_DOWNRIGHT: 
                        textView5.setText("Direction : Down Right");
                        command = "x";
                        break;
                    case joystickClass.STICK_DOWN: 
                        textView5.setText("Direction : Down");
                        command = "s";
                        break;                       
                    case joystickClass.STICK_DOWNLEFT: 
                        textView5.setText("Direction : Down Left");
                        command = "z";
                        break;
                    case joystickClass.STICK_LEFT:
                        textView5.setText("Direction : Left");
                        command = "a";
                        break;
                    case joystickClass.STICK_UPLEFT:
                        textView5.setText("Direction : Up Left");
                        command = "q";
                        break;
                    case joystickClass.STICK_NONE:
                        textView5.setText("Direction : Center");
                        command = "l";
                        break;
                    }
                    try
                        {

                        outputStream.write(command.getBytes());
                        }
                    catch(IOException e)
                    {
                        e.printStackTrace();
                    }


                }else if(arg1.getAction() == MotionEvent.ACTION_UP) {
                    textView1.setText("X :");
                    textView2.setText("Y :");
                    textView3.setText("Angle :");
                    textView4.setText("Distance :");
                    textView5.setText("Direction :");
                }

                return true;
            }
        });

        on_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                command = "7";
                try {
                    outputStream.write(command.getBytes());
                }
                catch(IOException e){
                    e.printStackTrace();
                }
            }
        });
        off_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                command = "6";
                try{
                    outputStream.write(command.getBytes());
                }
                catch (IOException e){
                    e.printStackTrace();
                }
            }
        });
        
         seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                reading.setText(progress + "% ");


                switch (progress){
                    case 1:
                        command = "1";
                        break;
                    case 2:
                        command = "2";
                        break;
                    case 3:
                        command = "3";
                        break;
                    case 4:
                        command = "4";
                        break;
                    case 5:
                        command = "5";
                        break;
                }

                try {
                    outputStream.write(command.getBytes());
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        });
        
        go_auto.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked == true){
                    command = "g";
                    try{
                        outputStream.write(command.getBytes());
                    }
                    catch(IOException e){
                        e.printStackTrace();
                    }
                    Toast.makeText(getBaseContext(), "Auto mode on", Toast.LENGTH_SHORT).show();
                }else {
                    Toast.makeText(getBaseContext(),"Auto mode off", Toast.LENGTH_SHORT).show();
                    command = "l";
                    try{
                        outputStream.write(command.getBytes());
                    }
                    catch(IOException e){
                        e.printStackTrace();
                    }
                }
            }
        });

        bluetooth_connect_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if(BTinit())
                {
                    BTconnect();

                }
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        while (true) {
                            byte[] buffer = new byte[256];
                            int bytes;
                            String readMessage;

                            try {
                                if (inputStream.available() != 0) {
                                    bytes = inputStream.read(buffer);
                                    readMessage = new String(buffer, 0, bytes);
                                    handleInput(readMessage);
                                }
                            } catch (IOException exc) {
                                Log.e("IOException: ", exc.getMessage());
                            }
                            try {
                                Thread.sleep(500);
                            } catch (InterruptedException ie) {
                                // do nothing
                            }
                            continue;
                        }
                    }
                }).start();

            }

        });
    }

    //Initializes bluetooth module
    public boolean BTinit(){
        boolean found = false;

        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        if(bluetoothAdapter == null) //Checks if the device supports bluetooth
        {
            Toast.makeText(getApplicationContext(), "Device doesn't support bluetooth", Toast.LENGTH_SHORT).show();
        }

        if(!bluetoothAdapter.isEnabled()) //Checks if bluetooth is enabled. If not, the program will ask permission from the user to enable it
        {
            Intent enableAdapter = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableAdapter,0);

            try
            {
                Thread.sleep(1000);
            }
            catch(InterruptedException e)
            {
                e.printStackTrace();
            }
        }

        Set<BluetoothDevice> bondedDevices = bluetoothAdapter.getBondedDevices();

        if(bondedDevices.isEmpty()) //Checks for paired bluetooth devices
        {
            Toast.makeText(getApplicationContext(), "Please pair the device first", Toast.LENGTH_SHORT).show();
        }
        else
        {
            for(BluetoothDevice iterator : bondedDevices)
            {
                if(iterator.getAddress().equals(DEVICE_ADDRESS))
                {
                    device = iterator;
                    found = true;
                    break;
                }
            }
        }

        return found;
    }


    public boolean BTconnect(){
        boolean connected = true;

        try
        {
            socket = device.createRfcommSocketToServiceRecord(PORT_UUID); //Creates a socket to handle the outgoing connection
            socket.connect();


            Toast.makeText(getApplicationContext(),
                    "Connection to bluetooth device successful", Toast.LENGTH_LONG).show();
        }
        catch(IOException e)
        {
            e.printStackTrace();
            connected = false;
        }

        if(connected)
        {
            try
            {

                System.out.println("success");
                inputStream = socket.getInputStream();
                outputStream = socket.getOutputStream();

            }
            catch(IOException e)
            {
                e.printStackTrace();
            }
        }

        return connected;
    }

    private void handleInput(String input) {
        double realSpeed = Double.parseDouble(input);
        realSpeed = realSpeed*10;
        int intspeed = (int)realSpeed;

        speed.setText(""+ intspeed);

    }



    @Override
    protected void onStart()
    {
        super.onStart();
    }

}

