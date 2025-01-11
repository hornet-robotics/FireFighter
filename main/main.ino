#include "Gyroscope.h"
#include "DriveBase.h"
#include "FanMotor.h"

// create subsystem instances (drive, ultrasonic, ect)
DriveBase drive;
Encoder encoder;
FanMotor fan;

const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;

int state = 0;

void setup() {
  // put your setup code here, to run once:
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);
  // encoder.init();
  // encoder.resetAngle();
  Serial.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //encoder.isMagnetDetected();
  //encoder.getAngle();
  //Serial.println(encoder.getWrapAngle());

  // switch(state) {
  //   case 0:
  //     drive.move(6);
  //     if (drive.atTargetPosition()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 1:
  //     drive.turn(90);
  //     if (drive.atTargetAngle()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 2:
  //     drive.turn(-90);
  //     if (drive.atTargetAngle()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 3:
  //     drive.move(-6);
  //     if (drive.atTargetPosition()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 4: 
  //     drive.stop();
  //     break;
  // }

  if (drive.getCurrentRobotAngle() > 5) {
    drive.resetGyro();
  }

  // // drive.moveForward();
  Serial.print(drive.getCurrentWheelPosition());
  Serial.print(", ");
  Serial.print(drive.getCurrentRobotAngle());
  Serial.print(", ");
  Serial.println(state);

  //Serial.println(drive.getCurrentWheelPosition());

  // Serial.print(encoder.isMagnetDetected());
  // Serial.print(", ");
  // Serial.println(drive.getCurrentWheelPosition());

  //drive.turnLeftDeg(90);
}
