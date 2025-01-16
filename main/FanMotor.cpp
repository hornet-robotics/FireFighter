#include "FanMotor.h"

void FanMotor::init(int p) {

  // power pins (+ and -)
  pin = p;

  esc.attach(pin);
  esc.writeMicroseconds(1500);
  delay(2000);
}
//start bl motor depending on speed percentage
void FanMotor::start(){
  esc.writeMicroseconds(speed * 10 + 1500);  
}

void FanMotor::stop(){
  esc.writeMicroseconds(1500);
}

//*getters and setters*//
void FanMotor::setSpeed(int per){
  speed = per;
}

int FanMotor::getSpeed(){
  return speed;
}
