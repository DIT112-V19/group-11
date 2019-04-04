#include <Smartcar.h>

const unsigned short LEFT_ODOMETER_PIN = 2;
const unsigned short RIGHT_ODOMETER_PIN = 3;
const unsigned long PRINT_INTERVAL = 100;
unsigned long previousPrintout = 0;

BrushedMotor leftMotor(8, 10, 9);
BrushedMotor rightMotor(12, 13, 11);
DifferentialControl control(leftMotor, rightMotor);

GY50 gyroscope(37);
DirectionlessOdometer leftOdometer(100);
DirectionlessOdometer rightOdometer(100);

int fTrigPin = 35; // pins for rear and front sensors
int fEchoPin = 39;
int rTrigPin = 7;
int rEchoPin = 6;

SR04 fSensor(fTrigPin, fEchoPin, 200);
SR04 rSensor(rTrigPin, rEchoPin, 100); // unused rear sensor

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  }

int fDistance = 0;

void loop() {
  fDistance = fSensor.getDistance();
  rDistance = rSensor.getDistance();
  if(fDistance >= 30 && fDistance != 0){ // not 0 to account for faulty readings
    goForward();
    } else{
      stop();
      }
  Serial.println(rSensor.getDistance());
}

void stop() {
  car.setSpeed(0);
}

void goForward(){
  car.setSpeed(70);
  }
