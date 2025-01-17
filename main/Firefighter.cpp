#include "Firefighter.h"

// define pins names and values here, makes it is easier to track

// Drivebase pins
const int MOTOR1_PIN1 = 6; // motor 1 is on right side of robot
const int MOTOR1_PIN2 = 5;
const int MOTOR2_PIN1 = 4; // motor 2 is on left side of robot
const int MOTOR2_PIN2 = 3;
const int PWM_PINA = 7; // pwm for motor 1
const int PWM_PINB = 2; // pwm for motor 2

// Ultrasonic sensor pins
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

// extinguisher
const int FAN_PIN = 13;


void Firefighter::init() {

  // add subsystem init here
  drive.init(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, PWM_PINA, PWM_PINB);
  fan.init(FAN_PIN);

  // init ultrasonics
  ultraFrontLeft.init(ECHO_PIN0, TRIG_PIN0);
  ultraBackLeft.init(ECHO_PIN1, TRIG_PIN1);
  ultraBackRight.init(ECHO_PIN2, TRIG_PIN2);
  ultraFrontRight.init(ECHO_PIN3, TRIG_PIN3);
}

//TODO: consider using Enums instead of int for state values so it is easier to modify algorithm


bool Firefighter::HtoA() {

  int state = 0;

  switch (state)
  {
  case 0: // Move forward until opening on right side
    drive.moveForward();

    if (openingOnRight()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 1: // shift to avoid colliding with juction after next turn
    drive.move(JUNCTION_FORWARD_BUFFER);

    if (drive.atTargetPosition()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 2: // Turn 90 degrees clockwise
    drive.turn(90);

    if (drive.atTargetAngle()) {
      drive.resetEncoder();
      drive.resetGyro();
      state++;
      drive.stop();
    }
    break;

  case 3: // Move forward until opening on right side
    drive.moveForward();

    if (openingOnRight()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 4: // shift to avoid colliding with juction after next turn
    drive.move(JUNCTION_FORWARD_BUFFER);

    if (drive.atTargetPosition()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 5: // Turn 90 degrees clockwise
    drive.turn(90);

    if (drive.atTargetAngle()) {
      drive.resetEncoder();
      drive.resetGyro();
      state++;
      drive.stop();
    }
    break;

  case 6: // Move forward robot length + buffer (enter room)
    drive.move(ROBOT_LENGTH + ROOM_FORWARD_BUFFER);

    if (drive.atTargetPosition()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 7: // Turn 90 degrees clockwise (scan room)
    drive.turn(90);

    if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
      returnAngle = drive.getCurrentRobotAngle();
      drive.resetEncoder();
      drive.resetGyro();
      state++;

      if (true /* ir.roomScan() != 0 */) {
        state  = -1; // got to extinguish state
        flameDetected = true;
      }
      else {
        state++;
      }

    }
    break;

  case 8:
    drive.turn(-90);

    if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
      returnAngle = drive.getCurrentRobotAngle();
      drive.resetEncoder();
      drive.resetGyro();

      if (true /* ir.roomScan() != 0 */) {
        state  = -1; // got to extinguish state
        flameDetected = true;
      }
      else {
        state++;
      }
    }
    break;

  case 9:
    drive.turn(180);

    if (drive.atTargetAngle()) {
      drive.resetEncoder();
      drive.resetGyro();
      state++;

    }
    break;

  case 10:
    drive.move(ROBOT_LENGTH + ROOM_FORWARD_BUFFER);

    if (drive.atTargetPosition()) {
      drive.resetEncoder();
      state++;
    }
    break;

  case 11:
    drive.turn(-90);

    if (drive.atTargetAngle()) {
      drive.resetEncoder();
      drive.resetGyro();
      state++;

    }
    break;

  case 12:
    return true; // complete
  
  case -1:
    if (extinguish()){
      state = 9; // go back and continue after fire detected
    }

    break;
  
  }

  return false; // not complete
}

bool Firefighter::AtoB() {

}

bool Firefighter::BtoC() {

}

bool Firefighter::CtoD() {

}

bool Firefighter::extinguish() {

}

bool Firefighter::AtoH() {

}

bool Firefighter::BtoH() {

}

bool Firefighter::CtoH() {

}

bool Firefighter::DtoH() {

}

bool Firefighter::openingOnRight() {
  return ultraFrontRight.measureDistance() > SIDE_OPENING_TOLERANCE && ultraBackRight.measureDistance() > SIDE_OPENING_TOLERANCE;
}

bool Firefighter::openingOnLeft() {
  return ultraFrontLeft.measureDistance() > SIDE_OPENING_TOLERANCE && ultraBackLeft.measureDistance() > SIDE_OPENING_TOLERANCE;

}

bool Firefighter::isFlameDetected() {
  return flameDetected;
}