#include <Smartcar.h>

const unsigned short LEFT_ODOMETER_PIN = 2;
const unsigned short RIGHT_ODOMETER_PIN = 3;
unsigned long beepInterval = 10;
unsigned long prevBeep = 0;

BrushedMotor leftMotor(8, 10, 9);
BrushedMotor rightMotor(12, 13, 11);
DifferentialControl control(leftMotor, rightMotor);

GY50 gyroscope(0);
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

const int yellowRight = 50;// LEDs pins
const int redRight = 49;
const int yellowLeft = 48;
const int redLeft = 47;

unsigned long yellowCurrent;// Declaring the different Current millis.
unsigned long redCurrent;
unsigned long yellowTurningCurrent;
unsigned long redTurningCurrent;
unsigned long redBackingCurrent;
unsigned long yellowBackingCurrent;

unsigned long previousYellowDrive = 0;// Declaring  the different Previous Millis.
unsigned long yellowTurnPrev = 0;
unsigned long redTurnPrev = 0;
unsigned long previousRedDrive = 0;
unsigned long yellowBackPrev = 0;
unsigned long redBackPrev = 0;

const long YellowDrivingInterval = 2700; // Declaring the different lighting intervals.
const long redDrivingInterval = 1500 ;
const long turningInterval = 200;
const long BackingInterval = 900;
const long stopInterval = 60;

const int buzzer = 51;// Declaring the Buzzer pin variables.
unsigned long lastPeriodStart;
const int beepOnDuration = 150;
const int beepPeriodDuration = 200;

char inChar = '1';

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  leftOdometer.attach(LEFT_ODOMETER_PIN, []() {
    leftOdometer.update();
  });
  rightOdometer.attach(RIGHT_ODOMETER_PIN, []() {
    rightOdometer.update();
  });

  pinMode(yellowRight, OUTPUT);
  pinMode(redRight, OUTPUT);
  pinMode(yellowLeft, OUTPUT);
  pinMode(redLeft, OUTPUT);


}

int fDistance = 0;
int rDistance = 0;
const unsigned long DISTANCE_PRINT_INTERVAL = 1000; // one second
unsigned long distancePrintToggle = 0;

unsigned long currentTime = 0;
int a = 0;
void loop() {
  handleInput();
  
  
  


currentTime = millis();
//Serial.println(fDistance);
/*if (fDistance < 15 && fDistance != 0) {
  stop();
  }
  /* if(rDistance < 10 && rDistance != 0){
     stop();
     }*/
// handleInput();
//printSpeed();

if(beep()){
  prevBeep = currentTime;
  }/*
  if(intervalCheck(DISTANCE_PRINT_INTERVAL, distancePrintToggle)){
  distancePrintToggle = currentTime;
  printDistance();
  printSpeed();
  }*/
}

void autoMode() {
  inChar = Serial.read();
  while (true) {
    fSensor.getDistance();
    inChar = Serial.read();
    if (inChar == 'l'){
      stop();
      }
    //setForward();
   // goForward();
    obstacleAvoidance();
    stop();
    delay(500);
    reverse();
    rotateOnSpot(90, 50);
    
  }
}

void obstacleAvoidance() {
  boolean go = true;
  while (go) {
    setForward();
    goForward();
    fDistance = fSensor.getDistance();

    if (fDistance < 15 && fDistance != 0) {
      go = false;
    }
    if(inChar == 'l'){
      break;
      }
  }
}

void printSpeed() {
  Serial.print(car.getSpeed());
  rightOdometer.update();
  leftOdometer.update();
}

boolean intervalCheck(unsigned long interval, unsigned long toggle) { // handles interval checking for a given interval and the respective toggle
  if (currentTime > distancePrintToggle + interval) {
    return true;
  } else {
    return false;
  }
}

boolean beep() {
  rDistance = rSensor.getDistance();
  Serial.println(rDistance);
  if (rDistance <= 50 && rDistance != 0) {
    beepInterval = rDistance * 20;

    if (currentTime > prevBeep + beepInterval) {
      beepingTone();
      return true;
    }
  }
  return false;
}

void printDistance() {
  if (fDistance == 0) {
    Serial.println("No Object Found In Front");
  } else {
    Serial.print("Front distance: ");
    Serial.println(fDistance);
  }
  if (rDistance == 0) {
    Serial.println("No Object Found Behind");
  } else {
    Serial.print("Rear distance: ");
    Serial.println(rDistance);
  }
}

void stop() {
  fSensor.getDistance();
  car.setSpeed(0);
}

void goForward() {
  car.setSpeed(70);
}

void reverse() {
  car.setSpeed(-60);
}

void handleInput() {
  while (Serial.available() > 0) {
    inChar = Serial.read();
    switch (inChar) {
      case 'w': // forward
        setForward();
        goForward();
        drivingLights();
        break;
      case 's': // reverse
        reverse();
        backingLights();
        break;
      case 'a': // turn left
        setLeft();
        leftTurnLights();
        break;
      case 'd': // turn right
        setRight();
        rightTurningLights();
        break;
      case 'l': // break
        stop();
        stopLights();
        break;
      case 'q': //forward left
        setForwardLeft();
        leftTurnLights();
        break;
      case 'e': //forward right
        setForwardRight();
        rightTurningLights();
        break;
      case 'z': //reverse left
        setReverseLeft();
        backingLights();
        break;
      case 'x': //reverse right
        setReverseRight();
        backingLights();
        break;
      case '5':
        digitalWrite(yellowRight, HIGH);
        digitalWrite(redRight, HIGH);
        digitalWrite(yellowLeft, HIGH);
        digitalWrite(redLeft, HIGH);
        Serial.println(inChar);
        Serial.println("LED is ON");
        break;
      case '6':
        digitalWrite(yellowRight, LOW);
        digitalWrite(redRight, LOW);
        digitalWrite(yellowLeft, LOW);
        digitalWrite(redLeft, LOW);
        Serial.println(inChar);
        Serial.println("LED is OFF");
        break;
      case 'g':
        autoMode();
        break;
    }
  }
}
void speedUp() {
  speed = speed + 20;
}

void speedDown() {
  speed = speed - 20;
}

void setForward()
{
  gyroscope.update();
  car.setAngle(0);

}
void setLeft() {
  car.setAngle(-70);

}
void setRight() {
  car.setAngle(70);

}
void setForwardLeft() {
  car.setAngle(-45);


}
void setForwardRight() {
  car.setAngle(45);


}
void setReverseLeft() {
  car.setAngle(-135);

}
void setReverseRight() {
  car.setAngle(135);

}

//LED lighting modes methods

void drivingLights() { // this method turns on the driving mode Lights.
  yellowCurrent = millis();
  if (yellowCurrent - previousYellowDrive >= YellowDrivingInterval) {
    digitalWrite(yellowRight, !digitalRead(yellowRight));
    digitalWrite(yellowLeft, !digitalRead(yellowLeft));
    previousYellowDrive = yellowCurrent;
  }

  redCurrent = millis();
  if (redCurrent - previousRedDrive >= redDrivingInterval) {
    digitalWrite(redRight, !digitalRead(redRight));
    digitalWrite(redLeft, !digitalRead(redLeft));
    previousRedDrive = redCurrent;
  }
}

void rightTurningLights() { // This method turns on right Lights while the car is turning Right.
  yellowTurningCurrent = millis();
  if (yellowTurningCurrent - yellowTurnPrev >= turningInterval) {
    digitalWrite(yellowRight, !digitalRead(yellowRight));
    yellowTurnPrev = yellowTurningCurrent;
  }
  redTurningCurrent = millis();
  if (redTurningCurrent - redTurnPrev >= turningInterval) {
    digitalWrite(redRight, !digitalRead(redRight));
    redTurnPrev = redTurningCurrent;
  }
}

void leftTurnLights() { // This methods turns on left lights while the car is turning left
  yellowTurningCurrent = millis();
  if (yellowTurningCurrent - yellowTurnPrev >= turningInterval) {
    digitalWrite(yellowLeft, !digitalRead(yellowLeft));
    yellowTurnPrev = yellowTurningCurrent;
  }
  redTurningCurrent = millis();
  if (redTurningCurrent - redTurnPrev >= turningInterval) {
    digitalWrite(redLeft, !digitalRead(redLeft));
    redTurnPrev = redTurningCurrent;
  }
}

void backingLights() { // This method turns on backing lights.
  yellowBackingCurrent = millis();
  if (yellowBackingCurrent - yellowBackPrev >= BackingInterval) {
    digitalWrite(yellowRight, !digitalRead(yellowRight));
    digitalWrite(yellowLeft, !digitalRead(yellowLeft));
    yellowBackPrev = yellowBackingCurrent;
  }
  redBackingCurrent = millis();
  if (redBackingCurrent - redBackPrev >= BackingInterval) {
    digitalWrite(redRight, !digitalRead(redRight));
    digitalWrite(redLeft, !digitalRead(redLeft));
    redBackPrev = redBackingCurrent;
  }
}

void stopLights() { // This method turns on stop Lights
  yellowTurningCurrent = millis();
  if (yellowTurningCurrent - yellowTurnPrev >= stopInterval) {
    digitalWrite(yellowRight, !digitalRead(yellowRight));
    yellowTurnPrev = yellowTurningCurrent;
  }
  redTurningCurrent = millis();
  if (redTurningCurrent - redTurnPrev >= stopInterval) {
    digitalWrite(redRight, !digitalRead(redRight));
    redTurnPrev = redTurningCurrent;
  }
  yellowTurningCurrent = millis();
  if (yellowTurningCurrent - yellowTurnPrev >= stopInterval) {
    digitalWrite(yellowLeft, !digitalRead(yellowLeft));
    yellowTurnPrev = yellowTurningCurrent;
  }
  redTurningCurrent = millis();
  if (redTurningCurrent - redTurnPrev >= stopInterval) {
    digitalWrite(redLeft, !digitalRead(redLeft));
    redTurnPrev = redTurningCurrent;
  }
}

void rotateOnSpot(int targetDegrees, int speed) {

  targetDegrees = targetDegrees * 0.87;

  speed = smartcarlib::utils::getAbsolute(speed);
  targetDegrees %= 360;
  if (!targetDegrees) return;

  if (targetDegrees > 0) {
    car.overrideMotorSpeed(speed, -speed);
  } else {
    car.overrideMotorSpeed(-speed, speed);
  }
  unsigned int initialHeading = car.getHeading();
  int degreesTurnedSoFar = 0;
  while (abs(degreesTurnedSoFar) < abs(targetDegrees)) {
    gyroscope.update();
    int currentHeading = car.getHeading();
    Serial.println(currentHeading);
    if ((targetDegrees < 0) && (currentHeading > initialHeading)) {

      currentHeading -= 360;
    } else if ((targetDegrees > 0) && (currentHeading < initialHeading)) {
      currentHeading += 360;
    }
    degreesTurnedSoFar = initialHeading - currentHeading;
  }
  stop();
}
// Beeping Method
void beepingTone() {
  if (millis() - lastPeriodStart >=beepPeriodDuration)
  {
    lastPeriodStart += beepPeriodDuration;
    tone(buzzer, 550, beepOnDuration); // play 550 Hz tone in background for 'beepOnDuration'
  }
}
