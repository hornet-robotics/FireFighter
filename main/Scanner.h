#pragma once
//roomCheck function


//int roomCheck(); //Should just check all three sensors for any return value, 
		//Returns if anything is found whatsoever

//int centering(); //Checks the status of all three sensors and makes adjustments accordingly
		//Should simply loop and occasionally call the move function with adjustments
		//to movement or with basic readouts of the flame sensors, to send to specialized
		//functions

//void extinguish(int flmR, int flmL, int flmM); //Blast the fucker
#ifndef Scanner_h
#define Scanner_h


#include "Arduino.h"


class Scanner
{
public:
	Scanner(int L, int R, int M);
	void begin(); //Starter from setup(), will set pinModes and such
	int roomScan();
	//int centering();
	//void extinguish(int flmL, int flmR, int flmM);

private:
	int sensRight;
	int sensLeft;
	int sensMid;

};


#endif
