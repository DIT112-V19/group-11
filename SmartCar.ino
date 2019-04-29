#include <Smartcar.h>
#include <Wire.h>
#include <SoftwareSerial.h>

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
int distance = 0;
int speed = 0;

SR04 fSensor(fTrigPin, fEchoPin, 200);
SR04 rSensor(rTrigPin, rEchoPin, 100);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);
SoftwareSerial BTSerial(0, 1); 

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
  if(fDistance < 30 && fDistance != 0){
    stop();
    }

  handleInput();

  /*if(beep()){
    prevBeep = currentTime;
    }

  if(intervalCheck(DISTANCE_PRINT_INTERVAL, distancePrintToggle)){
    distancePrintToggle = currentTime;
    printDistance();
    printSpeed();
    }*/
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

void handleInput(){
  while (Serial.available()>0){
    char inChar = Serial.read();
    switch (inChar) {
    case 'w': //rotate counter-clockwise
    setForward();
    break;
    case 's': //rotate clock-wise
      setBackwards();
      break;
    case 'a': //go forward
      setLeft();
      break;
    case 'd': //go backward
      setRight();
      break;
    case 'o': //turn back left
      upSpeed(&speed); 
        car.setSpeed(speed);
      break;
    case 'k': //turn back right
      downSpeed(&speed);
              car.setSpeed(speed);

      break;
      case 'l':
      car.setSpeed(0); break;
    default: //if you receive something that you don't know, just stop
    break;
    }
  }
}

void upSpeed(int *speed2) {
 *speed2 = 20+ *speed2;

}
void downSpeed(int *speed2) {
  *speed2 = -20 + *speed2 ;

}

void setForward()
{
  car.setAngle(0);
}
void setBackwards() {

}
void setLeft() {
  car.setAngle(-90);
}
void setRight() {
  car.setAngle(90);
}
