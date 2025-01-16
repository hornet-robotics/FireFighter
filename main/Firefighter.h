#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include "DriveBase.h"
#include "Ultrasonic.h"
#include "FanMotor.h"

class Firefighter {

  public:

  // subsystem instantiation
  DriveBase drive;
  Ultrasonic ultraFrontLeft;
  Ultrasonic ultraBackLeft;
  Ultrasonic ultraBackRight;
  Ultrasonic ultraFrontRight;

  FanMotor fan;
  
  void init(); // create instances of subsystems

  void HtoA();
  void AtoB();
  void BtoC();
  void CtoD();

  void extinguish();

  void AtoH();
  void BtoH();
  void CtoH();
  void DtoH();

  bool openingOnRight();
  bool openingOnLeft();

  bool flameDetected = false;

  private: 
  // units in inches
  float robotWidth = 0;
  float robotLength = 0;

  const float SIDE_OPENING_TOLERANCE = 20; // cm | used to determine how large value ultrasonic needs to detect to 
                                                // consider a gap a junction opening

  const float JUNCTION_FORWARD_BUFFER = 5; // in | used to shift robot a bit forward after junction opening so 
                                                // robot doesn't collide with wall
    
};