#include "Firefighter.h"

// define pins names and values here is it is easier to track
// Drivebase pins
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int pwmPinA = 10;
const int pwmPinB = 11;


void Firefighter::init() {
  // add subsystem init here
  drive.init(motor1Pin1, motor1Pin2, motor2Pin1, motor2Pin2, pwmPinA, pwmPinB);

  // add ultrasonic, IR, ect init here
}


void Firefighter::HtoA() {

  // example of subsystems being used

  while (/*ultrasonic does not detect opening* on right side*/) {
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

