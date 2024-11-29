#include "Ultrasonic.h"

// create subsystem instances to test(drive, ultrasonic, ect) 
Ultrasonic ultraFrontLeft;
//Ultrasonic ultraFrontRight;

const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;

void setup() {
  // put your setup code here, to run once:
  ultraFrontLeft.init(36, 37);
  // Serial.begin(2000000);
  // Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  ultraFrontLeft.measureDistance();
}