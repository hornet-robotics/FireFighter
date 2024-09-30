#line 1 "/home/jester/FireFighter/main/DriveBase.h"
#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library

class DriveBase {

  public:

  void init(int m1p1, int m1p2, int m2p1, int m2p2, int pwmA, int pwmB);

  // move function at set speed
  void moveForward(int speed);
  void moveBack(int speed);
  void turnRight(int speed);
  void turnLeft(int speed);


  // move functions that move at global speed:
  void moveForward();
  void moveBack();
  void turnRight();
  void turnLeft();

  void stop();

  void setGlobalSpeed(int pwm);
  int getGlobalSpeed();


  private: 

    int globalSpeed = 255;
    
    int motor1Pin1;
    int motor1Pin2;
    int motor2Pin1;
    int motor2Pin2;

    int pwmPin1;
    int pwmPin2;
    
};