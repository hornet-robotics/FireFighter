#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library

class DCMotor{
  
  public:

  void init(); //pin parameter
  
  void start();
  void stop();

  void setSpeed(int per); //set speed, [-50 = fully counter-clock], [50 = fully clockwise]
  int getSpeed();

  private:
    int speed = 255; 
    //pins >>>
    int ENA = 9;
    int IN1 = 23;
    int IN2 = 25;
};
