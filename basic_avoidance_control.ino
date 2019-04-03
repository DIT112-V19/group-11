#include <Smartcar.h>  const unsigned short LEFT_ODOMETER_PIN = 2; const unsigned short RIGHT_ODOMETER_PIN = 3; const unsigned long PRINT_INTERVAL = 100; unsigned long previousPrintout = 0;  BrushedMotor leftMotor(8, 10, 9); BrushedMotor rightMotor(12, 13, 11); DifferentialControl control(leftMotor, rightMotor);  GY50 gyroscope(37); DirectionlessOdometer leftOdometer(100); DirectionlessOdometer rightOdometer(100); int trigPin = 35; int echoPin = 39; SR04 sensor(trigPin, echoPin, 200); int distance = 0;  SmartCar car(control, gyroscope, leftOdometer, rightOdometer);  void setup() {   // put your setup code here, to run once:  Serial.begin(9600); Serial.setTimeout(100);  }  void loop() {   distance = sensor.getDistance();   Serial.println(distance);   goForward(50);    if (distance < 30 && distance != 0) {     turn();    }  }  void goForward(int velocity) {   car.setSpeed(velocity); }  void stop(){   car.setSpeed(0);   }  void turn(){     car.setAngle(120);      goForward(50);     delay(500);     car.setAngle(0);     delay(500);   }
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
int trigPin = 35;
int echoPin = 39;
SR04 sensor(trigPin, echoPin, 200);
int distance = 0;

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
Serial.setTimeout(100);

}

void loop() {
  distance = sensor.getDistance();
  Serial.println(distance);
  goForward(50);

  if (distance < 30 && distance != 0) {
    turn();
   }

}

void goForward(int velocity) {
  car.setSpeed(velocity);
}

void stop(){
  car.setSpeed(0);
  }

void turn(){
    car.setAngle(120);
     goForward(50);
    delay(500);
    car.setAngle(0);
    delay(500);
  }
