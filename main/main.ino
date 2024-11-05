#include "DriveBase.h"

// create subsystem instances (drive, ultrasonic, ect)
DriveBase drive;

const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;

void setup() {
  // put your setup code here, to run once:
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);

}

void loop() {
  // put your main code here, to run repeatedly:

  float oneRotation = 4 * 3.14;

  //drive.moveBackIn(oneRotation);
  //drive.turnLeft();
}