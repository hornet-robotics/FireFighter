#include "DriveBase.h"

// create subsystem instances (drive, ultrasonic, ect)
DriveBase drive;

const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int pwmPinA = 10;
const int pwmPinB = 11;

void setup() {
  // put your setup code here, to run once:
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);

}

void loop() {
  // put your main code here, to run repeatedly:

  float oneRotation = 4 * 3.14;

  drive.moveBackIn(oneRotation);
}