#include "Ultrasonic.h"

void Ultrasonic::init(int echoPin, int trigPin) {
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
}

float Ultrasonic::measureDistance() {
    float filterArray[20];

    // Taking multiple measurements and store in an array
    for (int sample = 0; sample < 20; sample++) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        float duration_us = pulseIn(echoPin, HIGH);
        float distance_cm = 0.017 * duration_us;
        filterArray[sample] = distance_cm;
        delay(30); // To avoid ultrasonic interference
    }

    // Sort array in ascending order
    for (int i = 0; i < 19; i++) {
        for (int j = i + 1; j < 20; j++) {
            if (filterArray[i] > filterArray[j]) {
                float temp = filterArray[i];
                filterArray[i] = filterArray[j];
                filterArray[j] = temp;
            }
        }
    }
    // The five smallest samples are considered as noise -> ignore it
    // The five biggest  samples are considered as noise -> ignore it
    double sum = 0;
    for (int sample = 5; sample < 15; sample++) {
        sum += filterArray[sample];
    }

    distance = sum / 10;

    // Serial.begin(2000000);
    // Serial.print("Distance: ");
    // Serial.print(distance);
    // Serial.println(" cm");

    // TODO: consider returning distance in inches (distance = distance / 2.54)
    return distance;
}