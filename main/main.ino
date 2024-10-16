#include "FanMotor.h"

// create subsystem instances (drive, ultrasonic, ect)
FanMotor testDrive;

void setup() {
  // put your setup code here, to run once:
  testDrive.init(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  testDrive.start();
  stopPause(1000);
  // testDrive.turnRight();
  // stopPause(1000);

}

// only used for testing
void stopPause(int time) {
  delay(time);
  testDrive.stop();
  delay(time);
}
