#line 1 "/home/jester/FireFighter/main/FanMotor.cpp"
#include "FanMotor.h"

void FanMotor::init(int m1p1, int m1p2, int m2p1, int m2p2, int pwmA, int pwmB) {

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
