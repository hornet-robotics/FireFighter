#include "Ultrasonic.h"

void Ultrasonic::init(int echoPin, int trigPin) {
    this->echoPin = echoPin;
    this->trigPin = trigPin;

    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

float Ultrasonic::measureDistance() {

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration_us = pulseIn(echoPin, HIGH);
    float distance_cm = 0.017 * duration_us;

    return distance_cm;
}