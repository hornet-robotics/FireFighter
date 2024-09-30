#include <Arduino.h>
#line 1 "/home/jester/FireFighter/main/main.ino"
#include "DriveBase.h"

// create subsystem instances (drive, ultrasonic, ect)
DriveBase testDrive;

#line 6 "/home/jester/FireFighter/main/main.ino"
void setup();
#line 13 "/home/jester/FireFighter/main/main.ino"
void loop();
#line 26 "/home/jester/FireFighter/main/main.ino"
void stopPause(int time);
#line 6 "/home/jester/FireFighter/main/main.ino"
void setup() {
  // put your setup code here, to run once:
  
  testDrive.init(2, 3, 4, 5, 10, 11); // setup motor pin locations

}

void loop() {
  // put your main code here, to run repeatedly:

  testDrive.setGlobalSpeed(255);

  testDrive.moveForward();
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
#line 1 "/home/jester/FireFighter/main/test.ino"
int ledPin = 13;

void setup(){
  pinMode(ledPin, OUTPUT);
}

void loop(){
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

