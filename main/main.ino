#include "DriveBase.h"

// create subsystem instances (drive, ultrasonic, ect)
DriveBase testDrive;

void setup() {
  // put your setup code here, to run once:
  //ena = pwmA
  //enb = pwmB
  
  testDrive.init(6, 7, 8, 9, 5, 10); // setup motor pin locations

}

void loop() {
  // put your main code here, to run repeatedly:

  testDrive.setGlobalSpeed(255);

  testDrive.moveForward();
  //stopPause(1000);
  // testDrive.turnRight();
  // stopPause(1000);

}

// only used for testing
void stopPause(int time) {
  delay(time);
  testDrive.stop();
  delay(time);
}