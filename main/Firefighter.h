#pragma once // acts as header gaurd

#include <Arduino.h> // include arduino library
#include "DriveBase.h"
#include "Ultrasonic.h"
#include "FanMotor.h"

class Firefighter {

  public:

  // subsystem instantiation
  DriveBase drive;
  Ultrasonic ultraFrontLeft;
  Ultrasonic ultraBackLeft;
  Ultrasonic ultraBackRight;
  Ultrasonic ultraFrontRight;

  FanMotor fan;
  
  void init(); // create instances of subsystems

  // return true when complete
  bool HtoA();
  bool AtoB();
  bool BtoC();
  bool CtoD();

  bool extinguish();

  bool AtoH();
  bool BtoH();
  bool CtoH();
  bool DtoH();

  bool openingOnRight();
  bool openingOnLeft();

  bool isFlameDetected();

  // enum StateHtoA {
  //   MOVE_UNTIL_OPENING,
  //   SHIFT_FORWARD,
  //   TURN_TO_JUNCTION,
  //   // CYCLE HERE ONCE
  //   ENTER_ROOM,
  //   SCAN_ROOM, 
  //   EXTINGUISH,
  //   UNSCAN_ROOM,
  //   TURN_180,
  //   LEAVE_ROOM,
  //   TURN_TO_PATH,
  //   END
  // };

  // enum StateHtoA stateHtoA = MOVE_UNTIL_OPENING;


  private: 

  bool flameDetected = false;

  float returnAngle = 0; // "turnAngle" during scan when flame is detected

  const float ROBOT_WIDTH = 33.5; // cm
  const float ROBOT_LENGTH = 27.5; // cm

  const float SIDE_OPENING_TOLERANCE = 20; // cm | used to determine how large value ultrasonic needs to detect to 
                                                // consider a gap a junction opening

  const float JUNCTION_FORWARD_BUFFER = 4; // in | used to shift robot a bit forward after junction opening so 
                                                // robot doesn't collide with wall
  
  const float ROOM_FORWARD_BUFFER = 5; // in | used when moving into a room

  // HtoA and AtoB state and cycle declearaction and intitialization
  int cycle = 0;

  enum StateHtoA {
    MOVE_UNTIL_OPENING,
    SHIFT_FORWARD,
    TURN_TO_JUNCTION,
    BEFORE_HALLWAY,
    // CYCLE HERE ONCE
    ENTER_ROOM,
    SCAN_ROOM, 
    EXTINGUISH,
    UNSCAN_ROOM,
    TURN_180,
    LEAVE_ROOM,
    TURN_TO_PATH,
    END
  };

  enum StateHtoA stateHtoA = MOVE_UNTIL_OPENING;
};

