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
int distance = 0;
int speed = 0;

SR04 fSensor(fTrigPin, fEchoPin, 200);
SR04 rSensor(rTrigPin, rEchoPin, 100);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);
const int yellowRight = 20;
const int redRight = 18;
const int yellowLeft = 21;
const int redLeft = 19;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  leftOdometer.attach(LEFT_ODOMETER_PIN, []() {
    leftOdometer.update();
  });
  rightOdometer.attach(RIGHT_ODOMETER_PIN, []() {
    rightOdometer.update();
  });

  pinMode(yellowRight,OUTPUT);
  pinMode(redRight,OUTPUT);
  pinMode(yellowLeft,OUTPUT);
  pinMode(redLeft,OUTPUT);
  
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
  Serial.println(fDistance);
  if(fDistance < 15 && fDistance != 0){
      stop();
      }
 /* if(rDistance < 10 && rDistance != 0){
      stop();
      }*/
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
    car.setSpeed(50);
  }

void reverse(){
    car.setSpeed(-40);
  }

void handleInput(){
  while (Serial.available()>0){
    char inChar = Serial.read();
    switch (inChar) {
    case 'w': // forward
    setForward();
    goForward();
    
    break;
    case 's': // reverse
      reverse();
      break;
    case 'a': // turn left
      setLeft();
      break;
    case 'd': // turn right
      setRight();
      break;
    case 'l': // break
      stop();
      break;
    case 'q': //forward left
      setForwardLeft();
      break;
    case 'e': //forward right
      setForwardRight();
      break;
    case 'z': //reverse left
      setReverseLeft();
      break;
      case 'x': //reverse right
      setReverseRight();
      break;
    case '5':                
       digitalWrite(yellowRight,HIGH);
       digitalWrite(redRight,HIGH);
       digitalWrite(yellowLeft,HIGH);
       digitalWrite(redLeft,HIGH);
       Serial.println(inChar);
       Serial.println("LED is ON");
      break;
    case '6':
       digitalWrite(yellowRight,LOW);
       digitalWrite(redRight,LOW);
       digitalWrite(yellowLeft,LOW);
       digitalWrite(redLeft,LOW);
        Serial.println(inChar);
        Serial.println("LED is OFF");
        }
    }
  }
void speedUp(){
  speed = speed + 20;
  }

void speedDown(){
  speed = speed - 20;
  }

void setForward()
{
  car.setAngle(0);
 
}
void setLeft() {
  car.setAngle(-70);
  
}
void setRight() {
  car.setAngle(70);
  
}
void setForwardLeft(){
  car.setAngle(-45);
  
  
}
void setForwardRight(){
  car.setAngle(45);
  
  
}
void setReverseLeft(){
  car.setAngle(-135);
   
}
void setReverseRight(){
  car.setAngle(135);
    
}
