#include <Smartcar.h>

const unsigned short LEFT_ODOMETER_PIN = 2;
const unsigned short RIGHT_ODOMETER_PIN = 3;
unsigned long beepInterval = 10;
unsigned long prevBeep = 0;

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
  leftOdometer.attach(LEFT_ODOMETER_PIN, []() {
    leftOdometer.update();
  });
  rightOdometer.attach(RIGHT_ODOMETER_PIN, []() {
    rightOdometer.update();
  });
  
  }

int fDistance = 0;
int rDistance = 0;
const unsigned long DISTANCE_PRINT_INTERVAL = 1000; // one second
unsigned long distancePrintToggle = 0;


unsigned long currentTime = 0;

void loop() {
  currentTime = millis();
  fDistance = fSensor.getDistance();
  rDistance = rSensor.getDistance();
  if(fDistance >= 30 || fDistance == 0){
    goForward();
    } else{
      stop();
      }

  if(beep()){
    prevBeep = currentTime;
    }

  if(intervalCheck(DISTANCE_PRINT_INTERVAL, distancePrintToggle)){
    distancePrintToggle = currentTime;
    printDistance();
    printSpeed();
    }
}

void printSpeed(){
  Serial.print("Speed: ");
  Serial.println(car.getSpeed());
  rightOdometer.update();
  leftOdometer.update();
  }

boolean intervalCheck(unsigned long interval, unsigned long toggle){ // handles interval checking for a given interval and the respective toggle
  if(currentTime > distancePrintToggle + interval){
    return true;
    } else{
      return false;
      }
  }

boolean beep(){
  if(rDistance <= 50 && rDistance != 0){
    beepInterval = rDistance * 20;
    
    if(currentTime > prevBeep + beepInterval){
      Serial.println("Beep"); // stand-in for actual audible beep
      return true;
      }
    }
    return false;
  }

void printDistance(){
  if(fDistance == 0){
    Serial.println("No Object Found In Front");
    } else{
      Serial.print("Front distance: ");
      Serial.println(fDistance);
      }
  if(rDistance == 0){
    Serial.println("No Object Found Behind");
  } else{
    Serial.print("Rear distance: ");
    Serial.println(rDistance);
    }
}

void stop() {
  car.setSpeed(0);
}

void goForward(){
  car.setSpeed(30);
  }
