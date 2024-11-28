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
  Serial.print("Angle Z: ");
  Serial.print(scope.getAngle());
  Serial.println(" degrees");

  delay(50);
}

// only used for testing
void stopPause(int time) {
  delay(time);
  testDrive.stop();
  delay(time);
}
