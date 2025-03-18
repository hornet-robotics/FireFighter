#include "DCMotor.h"

void DCMotor::init() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);
    
    analogWrite(ENA, speed);
}
//start bl motor depending on speed percentage
void DCMotor::start(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void DCMotor::stop(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

//*getters and setters*//
void DCMotor::setSpeed(int per){
  speed = per;
}

int DCMotor::getSpeed(){
  return speed;
}
