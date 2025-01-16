#include "Firefighter.h"

// define pins names and values here, makes it is easier to track

// Drivebase pins
const int MOTOR1_PIN1 = 6; // motor 1 is on right side of robot
const int MOTOR1_PIN2 = 5;
const int MOTOR2_PIN1 = 4; // motor 2 is on left side of robot
const int MOTOR2_PIN2 = 3;
const int PWM_PINA = 7; // pwm for motor 1
const int PWM_PINB = 2; // pwm for motor 2

// extinguisher
const int FAN_PIN = 13;

void Firefighter::init() {
  // add subsystem init here
  drive.init(MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_PIN1, MOTOR2_PIN2, PWM_PINA, PWM_PINB);
  fan.init(FAN_PIN);
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

