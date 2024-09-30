#line 1 "/home/jester/FireFighter/main/Firefighter.h"
#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include "DriveBase.h"

class Firefighter {

  public:

    // subsystem instantiation
    DriveBase drive;
    
    void init(); // create instances of subsystems
    void lookForJunc(); // will use: drive, ultrasonic
    void scanRoom(); // drive, ultrasonic, ir sensor
    void extinguish(); // drive, ultrasonic, ir sensor, ext mechanism

  private: 
    // which units (ask hardware)?
    float robotWidth = 0;
    float robotLength = 0;
    float robotHieght = 0;

    float sideTolerance = 0;
    float sideDistance = 0;
    
};