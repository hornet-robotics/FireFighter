#pragma once

#include <Arduino.h>

class Ultrasonic {

    public:

    // Ultrasonic sensor helper functions
    void init(int echoPin, int trigPin);
    float measureDistance();

    private:
    float distance;
    int echoPin;
    int trigPin;
};