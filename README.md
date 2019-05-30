# group-11 

## What is the project about?
A  remotely controllable car. A bluetooth module is connected to make the car be manually controllable from a mobile application. The car also have sensors that provide specific features like obstacle control, parking assistance and led-lights control.   

## Why are we doing this project?
It is an interesting challenge which would provide us with a project that can cover various areas of interest as well as provide a codebase that ideally will be easy to re-use for future projects.

### What problem does it solve?
It will provide a solid platform that can be re-used to interact with similar setups and allow for interactive controls of an rc car.

## How you are going to make it?
The arduino will hold the logic of the movements and safety measures, the arduino will be connected by serial (usb connection) and we will use the Bluetooth connection to control the car via an app on a cellular device. We will be able to control the speed and direction of the car through controls on the mobile app. 

### What kind of technology are we using?
Arduino (Mega), SR04 Sensor(ultrasonic), buzzer, android studio.

## Hardware and software architecture

To be able to test the project you need to download the bluetooth app from google play or upload the android studio code to a android device. The car will move according to the specific inputs it get from the bluetooth module, which will be decided by the button clicked in the android app. The car will read the input using serial communication from the bluetooth. The flowchart below explains how the car recieve inputs from the application and moves according to input.  

### Flowchart for bluetooth controler
![flow](https://user-images.githubusercontent.com/45367329/58162132-db193b00-7c81-11e9-9a7d-6f103c452f7d.png)



__________________________________________________________________________________________________________________________________________

## Final ReadMe






# Demonstration Video

https://www.youtube.com/watch?v=33cHNJ9j7Kc&feature=youtu.be


# What is the Purpose of our Project?

The purpose of our project is to deliver a high-quality RC car that can be enjoyed by all ages. In order to reach this goal, we tackled a few issues:

1. Responsive and Interactive Controls

We really felt that responsive controls can make or break a RC car since RC cars are designed around being controllable and it should be fun to drive! To address this properly, we felt a joystick was the way to go as joysticks are familiar and intuitive to use.


2. Parking Assistance / Collision Avoidance

If you're controlling the RC car from a considerable distance, it can be hard to see how close you are to certain objects or walls. To remedy this, we added a buzzer that buzzes with varying frequency depending on close you are to said object. This allows the driver to know how close they are to collision. This permits safe parking or just avoiding collision when reversing.


3. Easily Accessible Controller

Most RC cars come with a bulky controller that you have to lug around everywhere you go if you want to be able to control the car. We wanted to avoid this to make it easier on the user so we decided to develop an android app that pairs to the car via Bluetooth and acts as a controller. 


4. Automatic mode

Automatic mode, which can be toggled on via the app, is a mode where the car drives by itself and avoids collision using it's front and back sensors. It's a good way to showcase the car's abilities and test if it's sensors are functioning well. 



## Hardware Setup and configuration


# Bluetooth

We needed to communicate between the Arduino and mobile device so we could send commands and also information, to do this we used a Bluetooth module that we inserted onto the car and can be used with the Arduino to send and receive information. 

We open a Bluetooth connection in the mobile application when the user clicks the "connect" button. The Bluetooth connection consists of two parts, an "Output stream" which allows the mobile app to send information to the car and a "InputStream" which allows the mobile app to display data from the car. When the connection is successful it means it has found the RC car and they are able to communicate. 


# Arduino
We used Arduino as it was provided to us already and it's a intuitive and effective software that allows for easily programmable control of the RC car.

For the Arduino to communicate with the mobile application, it uses the Inputstream part of the Bluetooth connection to send data such as speed or bearing. In the Arduino code, to send information you use "Serial.write" and then whatever information you want to be sent over. The Android code for the mobile application then takes that information and writes into an array and then it can be read from there.


# Mobile Application 
To develop the app that allowed remote control of the RC car, we used Android Studio as we were already familar with Java and most devices run on Android software, allowing us to reach a majority of customers. 


The mobile application sends a signal of individual characters that the Arduino listens for and then reacts accordingly depending on what we told it to do in the case of that letter. For example, when you press forward on the joystick on your mobile phone, the character 'w' is sent to the Arduino code on the RC car, which then sets the car straight and sets the speed accordingly. 


# Buzzer
For parking assistance, we wanted an audio cue of how close you were to an object so you can avoid collision. The buzzer gave us this solution. We hooked the buzzer up to our RC car and in the Arduino we wrote the logic of depending on how close you are to an object based on the readings of the rear sensor, the buzzing increases.


# LED Lights

