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

bool Firefighter::HtoA() { //TODO: in a untested state


  switch (stateHtoA) {

    case MOVE_UNTIL_OPENING: // Move forward until opening on right side
      drive.moveForward();

      if (openingOnRight()) {
        drive.resetEncoder();
        stateHtoA = SHIFT_FORWARD;
      }
      break;

    case SHIFT_FORWARD: 
    //shift to avoid colliding with juction after next turn
      drive.move(JUNCTION_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = TURN_TO_JUNCTION;
      }
      break;

    case TURN_TO_JUNCTION: // Turn 90 degrees clockwise
      drive.turn(90);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();

        if (cycle == 0) {
          stateHtoA = BEFORE_HALLWAY;
          cycle++;
        }
        else {
          stateHtoA = ENTER_ROOM;
        }
      }
      break;

    case BEFORE_HALLWAY: 
     drive.moveForward();

      if (!openingOnRight()) {
        drive.resetEncoder();
        stateHtoA = MOVE_UNTIL_OPENING;
      }
      break;

    case ENTER_ROOM: // Move forward robot length + buffer (enter room)
      drive.move((ROBOT_LENGTH / 2.54) + ROOM_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = SCAN_ROOM;
      }
      break;

    case SCAN_ROOM: // Turn 90 degrees clockwise (scan room)
      drive.turn(90);

      if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();

        if (false /* ir.roomScan() != 0 */) {
          stateHtoA  = EXTINGUISH; // got to extinguish state
          flameDetected = true;
        }
        else {
          stateHtoA = UNSCAN_ROOM;
        }

      }
      break;

    case UNSCAN_ROOM:
      drive.turn(-90);

      if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();

        if (false /* ir.roomScan() != 0 */) {
          stateHtoA  = EXTINGUISH; // got to extinguish state
          flameDetected = true;
        }
        else {
          stateHtoA = TURN_180;
        }
      }
      break;

    case TURN_180:
      drive.turn(180);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();
        stateHtoA = LEAVE_ROOM;

      }
      break;

    case LEAVE_ROOM:
      drive.move((ROBOT_LENGTH / 2.54) + ROOM_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = TURN_TO_PATH;
      }
      break;

    case TURN_TO_PATH:
      drive.turn(-90);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();
        stateHtoA = END;

      }
      break;

    case END:
      return true; // complete
    
    // case EXTINGUISH:
    //   if (extinguish()){
    //     stateHtoA = TURN_180; // go back and continue after fire detected
    //   }

    //   break;
  
  }

  return false; // not complete
}

bool Firefighter::AtoB() {
  HtoA();
}

bool Firefighter::BtoC() {
  switch (stateHtoA) {
    case MOVE_UNTIL_OPENING: // Move forward until opening on right side
      drive.moveForward();

      if (openingOnRight()) {
        drive.resetEncoder();
        stateHtoA = SHIFT_FORWARD;
      }
      break;
    
    case SHIFT_FORWARD: 
    // shift to avoid colliding with juction after next turn
      drive.move(JUNCTION_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = TURN_TO_JUNCTION;
      }
      break;

    case TURN_TO_JUNCTION: // Turn 90 degrees clockwise
      drive.turn(90);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();
        stateHtoA = ENTER_ROOM;
      }
      break;

    case ENTER_ROOM: // Move forward robot length + buffer (enter room)
    drive.stop();
      // drive.move((ROBOT_LENGTH / 2.54) + ROOM_FORWARD_BUFFER);

      // if (drive.atTargetPosition()) {
      //   drive.resetEncoder();
      //   stateHtoA = SCAN_ROOM;
      // }
      break;

    case SCAN_ROOM: // Turn 90 degrees clockwise (scan room)
      drive.turn(90);

      if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();

        if (false /* ir.roomScan() != 0 */) {
          stateHtoA  = EXTINGUISH; // got to extinguish state
          flameDetected = true;
        }
        else {
          stateHtoA = UNSCAN_ROOM;
        }

      }
      break;

    case UNSCAN_ROOM:
      drive.turn(-90);

      if (drive.atTargetAngle() /* || ir.roomScan() != 0 */) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();

        if (false /* ir.roomScan() != 0 */) {
          stateHtoA  = EXTINGUISH; // got to extinguish state
          flameDetected = true;
        }
        else {
          stateHtoA = TURN_180;
        }
      }
      break;

    case TURN_180:
      drive.turn(180);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();
        stateHtoA = LEAVE_ROOM;

      }
      break;

    case LEAVE_ROOM:
      drive.move((ROBOT_LENGTH / 2.54) + ROOM_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = TURN_TO_PATH;
      }
      break;

    case TURN_TO_PATH:
      drive.turn(-90);

      if (drive.atTargetAngle()) {
        drive.resetEncoder();
        drive.resetGyro();
        stateHtoA = END;

      }
      break;

    case END:
      return true; // complete
    }
    return false; // not complete

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