#include "DriveBase.h"

// :: is scope resolution operator
// allows the use of private variables from header within function body

void DriveBase::init(int m1p1, int m1p2, int m2p1, int m2p2, int pwmA, int pwmB) {

  // setup encoder
  encoder.init();
  encoder.resetAngle();

  // stup PID
  movePID = new PIDController(moveP);

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

// will need to delete Move obj since initialized using dynamic storage duration method
// used to prevent memory leaks
void DriveBase::freeMemory() {
  delete movePID;
}

// movement functions at set speed
void DriveBase::moveForward(int speed) {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::moveBack(int speed) {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::turnRight(int speed) {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);

  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  analogWrite(pwmPin1, speed);
	analogWrite(pwmPin2, speed);
}

void DriveBase::turnLeft(int speed) {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);

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

// move functions at set position (in)
void DriveBase::moveForwardIn(float position) {
  float error = position - getCurrentWheelPosition(); // calculate error
  float command = movePID->update(error); // get command determined by PID conroller 
                                //(using Arrow Operator to dereference movePID pointer then accessing update)
  // adjust speed based on command value (if at postion command will be 0)
  moveForward(command);
}

void DriveBase::moveBackIn(float position) {
  float error = position - getCurrentWheelPosition(); // calculate error
  float command = movePID->update(error); // get command determined by PID conroller
                                  //(using Arrow Operator to dereference movePID pointer then accessing update)
  // adjust speed based on command value (if at postion command will be 0)
  moveBack(command);
}


// turning fuctions at set angle (deg)
void DriveBase::turnRightDeg(float angle) {

}

void DriveBase::turnLeftDeg(float angle) {

}

void DriveBase::stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);

  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}


float DriveBase::getCurrentWheelPosition() {
  return encoder.getAngle() * ENCODER_RATIO * (WHEEL_DIAMETER * M_PI / 360);
}

float DriveBase::getCurrentWheelDegree() {
  return encoder.getAngle() * ENCODER_RATIO;
}

// getters and setters
void DriveBase::setGlobalSpeed(int pwm) {
  globalSpeed = pwm;
}

int DriveBase::getGlobalSpeed() {
  return globalSpeed;
}
