#include "Gyroscope.h"
#include "DriveBase.h"

// create subsystem instances (drive, ultrasonic, ect)
Gyroscope scope;
DriveBase testDrive;

void setup() {
  // put your setup code here, to run once:
  scope.init();
}

void loop() {
  Serial.println(scope.getAngle());

  delay(50);
}
