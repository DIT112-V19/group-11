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
