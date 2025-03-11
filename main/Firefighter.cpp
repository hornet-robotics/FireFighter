#include "Firefighter.h"

//comment test

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

//scanner, flame sensor pins NOTE: ENSURE POTENTIOMETER OF MIDDLE SENSOR IS MAX, L/R SENSORS ARE 2/3RDS OF MAX STRENGTH TO CONTROL GREYAREA (L AND R BUT NO MID)
const int SCAN_PIN_L = 42;
const int SCAN_PIN_R = 44;
const int SCAN_PIN_M = 46;

void Firefighter::init() {

  // add subsystem init here
  drive.init(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, PWM_PINA, PWM_PINB);
  fan.init(FAN_PIN);
  scan.init(SCAN_PIN_L, SCAN_PIN_R, SCAN_PIN_M);

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

    case SHIFT_FORWARD: // shift to avoid colliding with juction after next turn
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
        drive.stop();

        if (cycle == 0) {
          stateHtoA = MOVE_UNTIL_OPENING;
          cycle++;
        }
        else {
          stateHtoA = ENTER_ROOM;
        }
      }
      break;

    case ENTER_ROOM: // Move forward robot length + buffer (enter room)
      drive.move(ROBOT_LENGTH + ROOM_FORWARD_BUFFER);

      if (drive.atTargetPosition()) {
        drive.resetEncoder();
        stateHtoA = SCAN_ROOM;
      }
      break;

    case SCAN_ROOM: // Turn 90 degrees clockwise (scan room)
      drive.turn(90);

      if (drive.atTargetAngle() || scan.roomScan() != 0) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();


        if (scan.roomScan() != 0) {
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

      if (drive.atTargetAngle() || scan.roomScan() != 0) {
        returnAngle = drive.getCurrentRobotAngle();
        drive.resetEncoder();
        drive.resetGyro();

        if (scan.roomScan() != 0) {
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
      drive.move(ROBOT_LENGTH + ROOM_FORWARD_BUFFER);

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
    
    case EXTINGUISH:
      if (extinguish()){
        stateHtoA = TURN_180; // go back and continue after fire detected
      }

      break;
  
  }

  return false; // not complete
}

bool Firefighter::AtoB() {
  HtoA();
}

bool Firefighter::BtoC() {

}

bool Firefighter::CtoD() {

}

bool Firefighter::extinguish() {
  int extCounter = 0; //Counts how many times the robot adjusts while extinguishing the flame
  int greyCounter = 0; //Counts how many times the robot adjusts for the grey area
	
  //FLAG VALUES FROM SCANNER CLASS
        float firstRun = -999;
        float greyArea = -888;
        float flameExt = -777;
        float flameCentered = 0; //Check Scanner.cpp for explanations

  	float activeAngle = firstRun; //activeAngle is used to send and recieve angle used for adjusting robot, 
			    //starting value of -999 is flag for centering() function in Scanner class

  while (scan.roomScan() == true)
  {
    activeAngle = scan.centering(activeAngle);

    if (activeAngle == greyArea) //FLAG VALUE, tells robot to back up (flame found in scanner grey area)
    {
      drive.move(-1);
      greyCounter++;
      activeAngle = scan.Centering(greyArea);
    } 
    else if (activeAngle == 0)
    {
      fan.start();
      //delay(100); //Check syntax
      while (scan.roomScan)
      {
        drive.move(1);
        extCounter++;
      }
      drive.turn(scan.centering(flameExt));
      drive.move(-1  * ((extCounter * 3) + (greyCounter * 1))); //Combines total movement while adjusting to find the flame, used to return to entry position
    }
    else
    {
      drive.turn(activeAngle);
    }
  }
  return true; //ONLY WHEN FLAME IS NO LONGER FOUND

      drive.move(-1);
      greyCounter++;
      activeAngle = scan.centering(greyArea);
    } 
    else if (activeAngle == 0)
    {
      drive.stop();
      Serial.print("Yippee");
    //   fan.start();
    //   //delay(100); //Check syntax
    //   while (scan.roomScan)
    //   {
    //     drive.move(1);
    //     extCounter++;
    //   }
    //   drive.turn(scan.centering(flameExt));
    //   drive.move(-1  * ((extCounter * 3) + (greyCounter * 1))); //Combines total movement while adjusting to find the flame, used to return to entry position
    // }
      drive.turn(scan.centering(flameExt));
      drive.move(-1  * ((extCounter * 3) + (greyCounter * 1)));
    }
    else
    {
      drive.stop();
      //drive.turn(activeAngle);
    }
  }
  return true; //ONLY WHEN FLAME IS NO LONGER FOUND

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
