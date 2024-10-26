#pragma once

#include <Arduino.h>
#include <Wire.h>

class Encoder {
    public:

    void init();
    void resetAngle();

    float getAngle();
    float getWrapAngle();

    bool isMagnetHigh();
    bool isMagnetLow();
    bool isMagnetDetected();

    private:

    int lowByte; // raw angle 7:0
    word highByte; // raw angle 11:8
    int rawAngle;
    int startAngle = 0;
    int wrapAngle;
    int globalAngle;
    int quadrant = 1;
    int lastQuadrant = 1;

    const int SENSOR_ADDRESS = 0x36; // I2C sensor address

    int readRawAngle();
}