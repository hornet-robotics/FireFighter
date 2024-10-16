#include "DriveBase.h"

// :: is scope resolution operator
// allows the use of private variables from header within function body

void DriveBase::init(int m1p1, int m1p2, int m2p1, int m2p2, int pwmA, int pwmB) {

  // power pins (+ and -)
  motor1Pin1 = m1p1;
  motor1Pin2 = m1p2;
  motor2Pin1 = m2p1;
  motor2Pin2 = m2p2;

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // pwm pins
  pwmPin1 = pwmA;
  pwmPin2 = pwmB;

  pinMode(pwmPin1, OUTPUT);
  pinMode(pwmPin2, OUTPUT);
}

///////////////////TODO will need to change directions based on motor placement on final robot (forward, back, left, right)
// movement functions at set speed
void DriveBase::moveForward(int speed) {
  //right side
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  //left side
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::moveBack(int speed) {
  //right side
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  //left side
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::turnRight(int speed) {
  //right side
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  //left side
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::turnLeft(int speed) {
  //right side
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  //left side
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

// overload movment functions

void DriveBase::moveForward() {
  moveForward(globalSpeed);
}

void DriveBase::moveBack() {
  moveBack(globalSpeed);
}

void DriveBase::turnRight() {
  turnRight(globalSpeed);
}

void DriveBase::turnLeft() {
  turnLeft(globalSpeed);
}

void DriveBase::stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// getters and setters
void DriveBase::setGlobalSpeed(int pwm) {
  globalSpeed = pwm;
}

int DriveBase::getGlobalSpeed() {
  return globalSpeed;
}
