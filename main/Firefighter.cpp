#include "Firefighter.h"

// define pins names and values here is it is easier to track
// Drivebase pins
const int motor1Pin1 = 6;
const int motor1Pin2 = 5;
const int motor2Pin1 = 4;
const int motor2Pin2 = 3;
const int pwmPinA = 7;
const int pwmPinB = 2;
const int fanpin = 13;

void Firefighter::init() {
  // add subsystem init here
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);
  scope.init();
  fan.init(fanpin);
}


void Firefighter::HtoA() {

  // example of subsystems being used

<<<<<<< HEAD
=======

  while (true/*ultrasonic does not detect opening* on right side*/) {
    drive.moveForward();
  }
>>>>>>> 151a95d8515c89bda28bd48b81a4749f3cfc657d

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

