#include "Ultrasonic.h"
#include "DriveBase.h"

// create subsystem instances to test(drive, ultrasonic, ect) 
Ultrasonic ultraFrontLeft;
Ultrasonic ultraBackLeft;
Ultrasonic ultraBackRight;
Ultrasonic ultraFrontRight;
DriveBase drive;

const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;

// front left
const int ECHO_PIN0 = 30;
const int TRIG_PIN0 = 31;
// back left
const int ECHO_PIN1 = 32;
const int TRIG_PIN1 = 33;
// back right
const int ECHO_PIN2 = 34;
const int TRIG_PIN2 = 35;
// front right
const int ECHO_PIN3 = 36;
const int TRIG_PIN3 = 37;

void setup() {
  // put your setup code here, to run once:
  ultraFrontLeft.init(ECHO_PIN0, TRIG_PIN0);
  ultraBackLeft.init(ECHO_PIN1, TRIG_PIN1);
  ultraBackRight.init(ECHO_PIN3, TRIG_PIN2);
  ultraFrontRight.init(ECHO_PIN3, TRIG_PIN3);
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);

  // Serial.begin(2000000);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Serial.println(ultraFrontRight.measureDistance());

  if (ultraFrontRight.measureDistance() > 10 && ultraFrontRight.measureDistance() > 10) {
    // junction at right
    drive.turnRightDeg(90);
    Serial.println("turn"); //TODO: response seems too slow, must fix

  } 
  else {
    drive.moveForward();
    Serial.println("forward");
  }
}