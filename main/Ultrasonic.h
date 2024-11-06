#pragma once

#include <Arduino.h>

class Ultrasonic {

    public:
    float distance;

    // Ultrasonic sensor helper functions
    void init(int echoPin, int trigPin);
    float measureDistance();

    private:
    int echoPin;
    int trigPin;
};