#include "Arduino.h"
#include "Scanner.h"

void Scanner::init(int L, int R, int M)
{
	sensLeft = L/*pinnum*/;
	sensRight = R/*pinnum*/;
	sensMid = M/*pinnum*/;

	pinMode(sensLeft, INPUT);
    pinMode(sensRight, INPUT);
    pinMode(sensMid, INPUT);
}


bool Scanner::roomScan()
{
	LCheck = digitalRead(sensLeft);
	RCheck = digitalRead(sensRight);
	MCheck = digitalRead(sensMid);
	//Returns true if any combination of the flame sensors find a flame in the room
	if (!LCheck || !RCheck || !MCheck)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//FLAG VALUES USED IN CENTERING():
//-999 - Used on the first scan through to initialize the robot properly based on flame location
//-888 - Used to tell the robot to back up, used if flame is deteced in the scanner grey areas 
	//Scanner Grey areas are two regions slightly to left or right of middle scanner in which both left AND right are triggered
	//Where the robot cannot accurately determine which direction to move next
//-777 - Used only when flame has been succesfully extinguished, confirms the robot can now reset it's movement

float Scanner::centering(float inAngle) //TODO - FINISH LOGIC FOR 2nd CHECKS AND BEYOND, NEED TO FINALIZE
					//MATH FOR RETAINING AND SENDING REVERSION ANGLE AFTER FLAME 
					//IS GONE AND CREATE CASE WHEN FLAME IS CENTERED
{
	LCheck = digitalRead(sensLeft);
	RCheck = digitalRead(sensRight);
	MCheck = digitalRead(sensMid);

	if ((inAngle == -999 || inAngle == -888) && (MCheck) && (!RCheck || !LCheck)) //Only runs on first run through or flag values to keep revAngle accurate
	{
		if (!RCheck && LCheck)
		{
			sendAngle = 60;
			revAngle = -60;
			return sendAngle;
		}
		else if (!LCheck && RCheck)
		{
			sendAngle = -60;
			revAngle = 60;
			return sendAngle;
		}
		else if (!LCheck && !RightCheck) 
		{
			return -888; //FLAG VALUE, TELLS ROBOT TO BACK UP A BIT
		}
	}
	else if ((inAngle = -999 || inAngle == -888) && !MCheck) //Runs if after backing up, OR on the first scan, the flame is centered
	{
		return 0;
	}
	else if (inAngle == -777) //FLAG VALUE, Flame has been eliminated and robot must now correct and leave
	{
		return (revAngle * -1);
	}
	//END OF FIRST-RUN BLOCK
	
	//NEXT BLOCK HANDLES ALL ADJUSTMENTS FOR REGULAR CASES
	//revAngle = inAngle;
	if (!MCheck)
	{
		if (inAngle == -999)
		{
			revAngle = 0;
		}
		//Should we be so lucky that the robot wanders in a room and is immediately lined up with the flame

		if ((!RCheck && !LCheck) || (RCheck && LCheck))
		{
			return 0; //Flame is centered
		}
		else if (!RCheck && LCheck)
		{
			sendAngle = 2;
			revAngle = revAngle + sendAngle; //Adjustment to keep relation to default position accurate
			return sendAngle;
		}
		else if (!LCheck && RCheck)
		{
			sendAngle = -2;
			revAngle = revAngle + sendAngle;
			return sendAngle;
		}
	}
	else if(inAngle < 0)
	{
	//Previous turn was negative (flame previously on left)
		if (!RCheck && LCheck)
		{
			sendAngle = ((inAngle / 2) * -1);
			revAngle = revAngle + (sendAngle * -1);
			return sendAngle;
		}
		else if (!LCheck && RCheck)
		{
			sendAngle = (inAngle / 2);
			revAngle = revAngle + sendAngle;
			return sendAngle;
		}
	}
	else if(inAngle > 0)
	{
		//Previous turn angle was positive (flame previously on right)
		if (!RCheck && LCheck)
		{
			sendAngle = (inAngle / 2);
			revAngle = revAngle + (sendAngle * -1);
			return sendAngle;
		}
		else if (!LCheck && RCheck)
		{
			sendAngle = ((inAngle / 2) * -1);
			revAngle = revAngle + sendAngle;
			return sendAngle;
		}
	}
}

	//Essentially works the same as the binary search, starts by determining if the flame is:
	//	Left: -60 degrees
	//	Right: 60 degrees
	//	Reason: dead center is 0, left sweep is negative angle, right sweep is positive sweep
	//
	//Essentially cuts the sweep angle in half until the middle sensor is consistently
	//finding a flame or until middle AND L/R are finding a flame
	//
	//IMPORTANT: if L and R find a flame and middle does not, cut remaining adjustment by 3 instead 
	//of 2, save the data, and get ready to Extinguish()
	//
	//TURN VALUE: Each time, the turn value will be the adjusted to rotate the robot, starting 
	//with 60 degrees in the direction of the flame and cutting in half and flipping negative value
	//when neccessary (EX: if rotating -60 ends with the flame in the right area, flip negative, if 
	//+30 degree turn ends with flame in left area flip again, if flame is still in right area, DO
	//NOT FLIP NEGATIVE) 
	//
	//Return value will be what is necessary to return robot to entry angle, and will be the
	//+/- inverse of the final angle (EX: if -60 turn eliminates fire, turn +60 to return to dead 0 
	//
	//RETURN VALUE: (NEED TO FIND) Should be opposite +/- in relation to first turn, 

