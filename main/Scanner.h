#pragma once
//roomCheck function
//centering function
//extinguish function



#ifndef Scanner_h
#define Scanner_h

#include <Arduino.h>
//#include "Firefighter.h"

class Scanner
{
public:
	void init(int L, int R, int M);
	bool roomScan();
	float centering(float inAngle);
	//void extinguish(int flmR, int flmL, int flmM);

private:
	int sensRight;
	int sensLeft;
	int sensMid;

	//Following used to hold sensor inputs when checking for flame
	//So I don't have to type "digitalRead(sens) three billion times"
	bool LCheck; 
	bool RCheck;
	bool MCheck;
	//Reminder: digitalRead will send 0(false) if flame is found and 1(true) if no flame is found

	float revAngle = 0; //Angle used to send robot back to starting position
	float sendAngle = 0; //Angle being sent to adjust robot
};


#endif
