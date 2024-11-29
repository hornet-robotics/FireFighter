#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include "DriveBase.h"
#include "Gyroscope.h"

class Firefighter {

  public:

    // subsystem instantiation
    DriveBase drive;
    Gyroscope scope;
    
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

    void openingOnRight();
    void openingOnLeft();

    bool flameDetected = false;

  private: 
    // which units (ask hardware)?
    float robotWidth = 0;
    float robotLength = 0;
    float robotHieght = 0;

    float sideTolerance = 0;
    float sideDistance = 0;

    float buffer = 0; // might need to be local var
    
};