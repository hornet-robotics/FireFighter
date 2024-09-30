#include "FanMotor.h"

void FanMotor::init(int p) {

  // power pins (+ and -)
  pin = p;

  esc.attach(pin);
  esc.writeMicroseconds(1000);
  delay(2000);
}
//start bl motor depending on speed percentage
void FanMotor::start(){
  esc.writeMicroseconds(speed * 10 + 1000)  
}

void FanMotor::stop(){
  esc.writeMicroseconds(1000);
}

//*getters and setters*//
void FanMotor::setSpeed(int per){
  speed = per;
}

void FanMotor::getSpeed(){
  return speed;
}
