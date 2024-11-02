#include "DriveBase.h"
#include "Encoder.h"

// create subsystem instances (drive, ultrasonic, ect)
Encoder encoder;

void setup() {
  // put your setup code here, to run once:
  encoder.init();

  encoder.resetAngle();

}

void loop() {
  // put your main code here, to run repeatedly:

  encoder.getAngle();

}