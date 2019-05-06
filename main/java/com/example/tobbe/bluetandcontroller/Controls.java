package com.example.tobbe.bluetandcontroller;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class Controls extends AppCompatActivity {

    //declaring buttons etc
    Button goForwardBtn, reverseBtn, dcBtn, leftBtn, rightBtn, stopBtn;
    TextView textView;
    //declaring bluetooth stuff

    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private InputStream inputStream;
    private OutputStream outputStream;







    // stuff is passed over from Controls, everything is initialized here.
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_controls);

        // getting data passed over from DeviceList (the selected BT device), EXTRA_ADDRESS is a public variable in DeviceList class
        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS);

        //initializing buttons
        goForwardBtn = (Button)findViewById(R.id.goForwardBtn);
        reverseBtn = (Button)findViewById(R.id.reverseBtn);
        dcBtn = (Button)findViewById(R.id.dcBtn);
        rightBtn = (Button)findViewById(R.id.rightBtn);
        leftBtn = (Button)findViewById(R.id.leftBtn);
        stopBtn = (Button)findViewById(R.id.stopBtn);
        textView = (TextView)findViewById(R.id.textView);


        //Call the connectBT method to connect to the selected BT device
        new ConnectBT().execute();


        //here we decide what the button clicks will do
        //We are calling a method with every button click

        stopBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stop();
            }
        });
        leftBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goLeft();
            }
        });
        rightBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                goRight();

            }
        });
        goForwardBtn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                goForward();
            }
        });

        reverseBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                reverse();
            }
        });

        dcBtn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect(); //close connection
            }
        });


    }


    //method that takes a string and shows it across the screen, for example "connecting to device...."
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }


    //the methods  that are called through buttonclicks


    private void Disconnect()
    {
        if (btSocket!=null) //If the btSocket is busy
        {
            try
            {
                btSocket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout
    }
    private void stop()
    {
        if (btSocket!=null)
        {
            try
            {
                String stop = "l";
                btSocket.getOutputStream().write(stop.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void goRight()
    {
        if (btSocket!=null)
        {
            try
            {
                String goRight = "d";
                btSocket.getOutputStream().write(goRight.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void goLeft()
    {
        if (btSocket!=null)
        {
            try
            {
                String goLeft = "a";
                btSocket.getOutputStream().write(goLeft.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void reverse()
    {
        if (btSocket!=null)
        {
            try
            {
                String goBack = "s";
                btSocket.getOutputStream().write(goBack.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void goForward()
    {
        if (btSocket!=null)
        {
            try
            {
                String goForward = "w";
                btSocket.getOutputStream().write(goForward.getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }



    //This method initializes all the bluetooth stuff and shows neat messages while its connecting
    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute() {
            progress = ProgressDialog.show(Controls.this, "Connecting...", "Please wait...");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try {
                if (btSocket == null || !isBtConnected) {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();//start connection
                    inputStream = btSocket.getInputStream();

                }
            } catch (IOException e) {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess) {
                Toast.makeText(Controls.this, "Could not connect..", Toast.LENGTH_LONG).show();
                Intent intent = new Intent(Controls.this, DeviceList.class);
                startActivity(intent);
            } else {
                Toast.makeText(Controls.this, "Connected!", Toast.LENGTH_SHORT).show();
                isBtConnected = true;

                try {
                    outputStream = btSocket.getOutputStream();
                    inputStream = btSocket.getInputStream();

                } catch (IOException exc) {
                    Log.e("IOException: ", exc.getMessage());
                }
                progress.dismiss();
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


        }

        private void handleInput(String input) {
            textView.setText("+" + input);
        }
    }

}




