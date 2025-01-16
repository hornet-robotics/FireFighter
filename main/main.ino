#include "Ultrasonic.h"
#include "DriveBase.h"
#include "FanMotor.h"

// create subsystem instances to test(drive, ultrasonic, ect) 
Ultrasonic ultraFrontLeft;
Ultrasonic ultraBackLeft;
Ultrasonic ultraBackRight;
Ultrasonic ultraFrontRight;
DriveBase drive;

const int MOTOR1_PIN1 = 6; // motor 1 is on right side of robot
const int MOTOR1_PIN2 = 5;
const int MOTOR2_PIN1 = 4; // motor 2 is on left side of robot
const int MOTOR2_PIN2 = 3;
const int PWM_PINA = 7; // pwm for motor 1
const int PWM_PINB = 2; // pwm for motor 2

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

int state = 0;


void setup() {
  // put your setup code here, to run once:
  ultraFrontLeft.init(ECHO_PIN0, TRIG_PIN0);
  ultraBackLeft.init(ECHO_PIN1, TRIG_PIN1);
  ultraBackRight.init(ECHO_PIN2, TRIG_PIN2);
  ultraFrontRight.init(ECHO_PIN3, TRIG_PIN3);
  drive.init(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, PWM_PINA, PWM_PINB);

  // Serial.begin(2000000);
  Serial.begin(9600);
  // encoder.init();
  // encoder.resetAngle();
  Serial.begin(2000000);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Serial.println(ultraBackRight.measureDistance());

  //TODO: response seems too slow, filtering and delay causes significant lag in response
  if (ultraFrontRight.measureDistance() > 10 && ultraBackRight.measureDistance() > 10) {
    // junction at right
    drive.stop();
    // Serial.println("turn");

  } 
  else {
    drive.moveForward();
    // Serial.println("forward");
  }

  // encoder.isMagnetDetected();
  // encoder.getAngle();
  // Serial.println(encoder.getWrapAngle());

  // switch(state) {
  //   case 0:
  //     drive.move(12);
  //     if (drive.atTargetPosition()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 1:
  //     drive.turn(90);
  //     if (drive.atTargetAngle()) {
  //       drive.resetEncoder();
  //       drive.resetGyro();
  //       state++;
  //     }
  //     break;

  //   case 2:
  //     drive.move(12);
  //     if (drive.atTargetPosition()) {
  //       state++;
  //       drive.stop();
  //       delay(500); // solves gyro angle increase during middle of run (see Gyroscope.h)
  //     }
  //     break;

  //   case 3:
  //     drive.move(0);
  //     if (drive.atTargetPosition()) {
  //       state++;
  //     }
  //     break;

  //   case 4:
  //     drive.turn(-90);
  //     if (drive.atTargetAngle()) {
  //       drive.resetEncoder();
  //       state++;
  //     }
  //     break;

  //   case 5:
  //     drive.move(-12);
  //     if (drive.atTargetPosition()) {
  //       state++;
  //     }
  //     break;

  //   case 6: 
  //     drive.stop();
  //     break;
  // }

  // Serial.print(drive.getCurrentWheelPosition());
  // Serial.print(", ");
  // Serial.print(drive.getCurrentRobotAngle());
  // Serial.print(", ");
  // Serial.println(state);
}
