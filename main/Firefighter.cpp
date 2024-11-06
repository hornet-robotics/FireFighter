#include "Firefighter.h"

// define pins names and values here is it is easier to track
// Drivebase pins
const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;

// Ultrasonic sensor pins
// front left
const int ECHO_PIN0 = 30;
const int TRIG_PIN0 = 31;
// front right
const int ECHO_PIN1 = 32;
const int TRIG_PIN1 = 33;


void Firefighter::init() {
  // init drive
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);

  // init ultrasonics
  ultraFrontLeft.init(ECHO_PIN0, TRIG_PIN0);
  ultraFrontRight.init(ECHO_PIN1, TRIG_PIN1);
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

void Firefighter::openingOnRight() {

}

void Firefighter::openingOnLeft() {

}

