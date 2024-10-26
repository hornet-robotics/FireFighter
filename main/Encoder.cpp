#include "Encdoer.h"

// sensor data sheet https://look.ams-osram.com/m/7059eac7531a86fd/original/AS5600-DS000365.pdf

void Encoder::init() {
    Wire.begin(); //start i2C (establish arduino as conroller/master device)
    // set clock for I2C
    Wire.setClock(800000L);
}

void Encoder::void resetAngle() {
    startAngle = (readRawAngle() * 0.08789) -  startAngle;
}

void Encoder::float getAngle() {
    
    // get angle in degrees (still has wrap around)
    float angle = getWrapAngle();

    // track "quadrant" (only need 3) to add or subtract 360 to prevent wrap around
    if (angle >= 0 && angle < 90) {
        quadrant = 1;
    }

    else if (angle >= 90 && angle < 270) {
        quadrant = 2;
    }

    else if (angle >= 270 && angle < 360) {
        quadrant = 3;
    }

    // react to transitions
    if (quadrant != lastQuadrant) {

        // check for 1-3 or 3-1 transitions
        if (lastQuadrant == 3 && quadrant == 1) {
            globalAngle += 360;
            glovalAngle + angle;
        }

        else if (lastQuadrant == 1 && quadrant == 3) {
            globalAngle -= 360;
            globalAngle + angle;
        }

        // update lastQuadrant
        lastQuadrant = quadrant;
    }
}

void Encoder::float getWrapAngle() {
    // convert angle in bits to degrees then track based on set origin
    wrapAngle  = readRawAngle() * 0.08789; // convert to degrees: x bits * (360 degrees per rev / 2^12 bits per rev)
    wrapAngle = wrapAngle - startAngle;

    return wrapAngle;
}

void Encoder::bool isMagnetHigh() {

}

void Encoder::bool isMagnetLow() {

}

void Encoder::bool isMagnetDetected(){
    Wire.beginTransmission(SENSOR_ADDRESS);
    Wire.write(0x0B); // 0x0C refers to register corresponding to STATUS
    Wire.endTransmission();
    Wire.requestFrom(SENSOR_ADDRESS, 1);

    // wait for proper return value then read
    while(Wire.available() == 0); // returns number of bytes avialable (1)
    int magnetStatus = Wire.read();

    return false;
}


void Encoder::int readRawAngle() {

    // work on 0x0D RAW ANGLE (7:0) - 8 bits
    Wire.beginTransmission(SENSOR_ADDRESS);
    // send bytes in a queue, tell what data we want to read from sensor
    Wire.write(0x0D); // 0x0D refers to register corresponding to RAW ANGLE(7:0)
    Wire.endTransmission();
    Wire.requestFrom(SENSOR_ADDRESS, 1); // requst 1 byte data from senosr

    // wait for proper return value then read
    while(Wire.available() == 0); // returns number of bytes avialable (1)
    lowByte = Wire.read();

    // work on 0x0C RAW ANGLE (11:8) - 4 bits
    Wire.beginTransmission(SENSOR_ADDRESS);
    // send bytes in a queue, tell what data we want to read from sensor
    Wire.write(0x0D); // 0x0C refers to register corresponding to RAW ANGLE(11:8)
    Wire.endTransmission();
    Wire.requestFrom(SENSOR_ADDRESS, 1); // requst 1 byte data from senosr

    // wait for proper return value then read
    while(Wire.available() == 0); // returns number of bytes avialable (1)
    highByte = Wire.read();

    // 4 bits have to be shifted to its proper place as we want to build a 12-bit number
    highbyte = highbyte << 8; // shifting to left
    // What is happening here is the following: The variable is being shifted by 8 bits to the left:
    // Initial value: 00000000|00001111 (word = 16 bits or 2 bytes)
    // Left shifting by eight bits: 00001111|00000000 so, the high byte is filled in.
    // Basically, the orignal far left bits didn't matter, and we shift to drop them and to make 
    // room for the low bye that will be added next
    
    // Finally, we combine (bitwise OR) the two numbers:
    // High: 00001111|00000000
    // Low:  00000000|00001111
    //      -----------------
    // H|L:  00001111|00001111
    // ^ basically left 4 bits don't matter so we essentially have a 12 bit value even though its actual length is 16


    rawAngle = highbyte | lowByte; // int is 16 bits (as well as the word)
    return rawAngle;
}