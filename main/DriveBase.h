#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include "PIDController.h"
#include "Encoder.h"
#include <math.h>

class DriveBase {

  public:

  void init(int m1p1, int m1p2, int m2p1, int m2p2, int pwmA, int pwmB);

  void freeMemory();

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

  // move functions at set position (in)
  void moveForwardIn(float position);
  void moveBackIn(float position);

  // turning fuctions at set angle (deg)
  void turnRightDeg(float angle);
  void turnLeftDeg(float angle);

  void stop();

  float getCurrentWheelPosition();
  float getCurrentWheelDegree();

  void setGlobalSpeed(int pwm);
  int getGlobalSpeed();

  private:

  const float GEARBOX_RATIO = 57.7;
  const float ENCODER_RATIO = 97.03/33.81; // 4 7/8 and 1 3/8
  const float WHEEL_DIAMETER = 4.875; // in

  int globalSpeed = 255; // default is 255 (max speed);
  
  int motor1Pin1;
  int motor1Pin2;
  int motor2Pin1;
  int motor2Pin2;

  int pwmPin1;
  int pwmPin2;

  float moveP = 20;

  PIDController* movePID; // declare obj using dynamic storage duration method
                          // allows usage of new keyword so obj can be initialized in .ccp init fuction
                          // will need to delete obj when not being used to prevent memory leaks
  Encoder encoder;
    
};