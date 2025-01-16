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


void Firefighter::HtoA() {

  // example of subsystems being used


  while (true/*ultrasonic does not detect opening* on right side*/) {
    drive.moveForward();
  }

  // continue from here as more subystems are finished...

  // consider using switch statement here?
}

void Firefighter::AtoB() {

}

void Firefighter::BtoC() {

}

void Firefighter::CtoD() {

}

void Firefighter::extinguish() {

}

void Firefighter::AtoH() {

}

void Firefighter::BtoH() {

}

void Firefighter::CtoH() {

}

void Firefighter::DtoH() {

}

bool Firefighter::openingOnRight() {
  return ultraFrontRight.measureDistance() > SIDE_OPENING_TOLERANCE && ultraBackRight.measureDistance() > SIDE_OPENING_TOLERANCE;
}

bool Firefighter::openingOnLeft() {
  return ultraFrontLeft.measureDistance() > SIDE_OPENING_TOLERANCE && ultraBackLeft.measureDistance() > SIDE_OPENING_TOLERANCE;

}

