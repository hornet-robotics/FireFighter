#include "Encoder.h"

// sensor data sheet https://look.ams-osram.com/m/7059eac7531a86fd/original/AS5600-DS000365.pdf

void Encoder::init() {
    Wire.begin(); //start i2C (establish arduino as conroller/master device)
    // set clock for I2C
    Wire.setClock(800000L);
}

void Encoder::resetAngle() {
    startAngle = (readRawAngle() * 0.08789) -  startAngle;
}

float Encoder::getAngle() {
    
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
            angleSum += 360;
        }

        else if (lastQuadrant == 1 && quadrant == 3) {
            angleSum -= 360;
        }

        // update lastQuadrant
        lastQuadrant = quadrant;
    }

    globalAngle = angleSum + angle;

    Serial.begin(2000000);
    Serial.println(globalAngle / GEARBOX_RAIO);

    return globalAngle;
}

float Encoder::getWrapAngle() {
    // convert angle in bits to degrees then track based on set origin
    // angle will wrape from 0 to 360
    wrapAngle  = readRawAngle() * 360.0f / 4096.0f; // convert to degrees: x bits * (360 degrees per rev / 2^12 bits per rev)
    wrapAngle = wrapAngle - startAngle;

    // sometimes angle changes to negative during spin, subtracting on negitive keeps cycle consistent
    if (wrapAngle < 0) {
        wrapAngle = 360 + wrapAngle;
    }

    // Serial.begin(2000000);
    // Serial.println(wrapAngle);

    return wrapAngle;
}

bool Encoder::isMagnetDetected(){
    Wire.beginTransmission(SENSOR_ADDRESS);
    Wire.write(0x0B); // 0x0C refers to register corresponding to STATUS
    Wire.endTransmission();
    Wire.requestFrom(SENSOR_ADDRESS, 1);

    // wait for proper return value then read
    while(Wire.available() == 0); // returns number of bytes avialable (1)
    int magnetStatus = Wire.read();

    //Serial.begin(2000000);
    //Serial.print("MD status: ");
    //Serial.println(magnetStatus, BIN);
    //Serial.println(magnetStatus);

    //MH: Too strong magnet - 100111 - DEC: 39 
    //ML: Too weak magnet - 10111 - DEC: 23     
    //MD: OK magnet - 110111 - DEC: 55

    return magnetStatus == 55;
}


int Encoder::readRawAngle() {

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
    Wire.write(0x0C); // 0x0C refers to register corresponding to RAW ANGLE(11:8)
    Wire.endTransmission();
    Wire.requestFrom(SENSOR_ADDRESS, 1); // requst 1 byte data from senosr

    // wait for proper return value then read
    while(Wire.available() == 0); // returns number of bytes avialable (1)
    highByte = Wire.read();

    // 4 bits have to be shifted to its proper place as we want to build a 12-bit number
    highByte = highByte << 8; // shifting to left
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

    rawAngle = highByte | lowByte; // int is 16 bits (as well as the word)

    // Serial.begin(2000000);
    // Serial.println(rawAngle);

    return rawAngle;
}