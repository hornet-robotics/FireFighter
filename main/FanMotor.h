#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include <Servo.h> //include Servo library

class FanMotor {
  
  public:

  void init(int p); //pin parameter
  
  void start();
  void stop();

  void setSpeed(int per); //set speed, percentage-wise
  void getSpeed();

  private:
    int speed = 10; 
    int pin;
    Servo esc;
};
