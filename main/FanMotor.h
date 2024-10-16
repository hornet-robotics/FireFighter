#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include <Servo.h> //include Servo library

class FanMotor {
  
  public:

  void init(int p); //pin parameter
  
  void start();
  void stop();

  void setSpeed(int per); //set speed, [-50 = fully counter-clock], [50 = fully clockwise]
  void getSpeed();

  private:
    int speed = -10; 
    int pin;
    Servo esc;
};
