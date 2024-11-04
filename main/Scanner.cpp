//SCANNER CLASS
//LARGELY COMPLETE

#include "Arduino.h"
#include "Scanner.h"

/*
void loop() {
  int scanResult; //Holds results of roomScan function, which are returned from the function

  scanResult = roomScan();

}
*/

Scanner::Scanner(int L, int R, int M)
{
	sensLeft = L/*pinnum*/;
	sensRight = R/*pinnum*/;
	sensMid = M/*pinnum*/;
}



void Scanner::begin()
{
	pinMode(sensLeft, INPUT);
	pinMode(sensRight, INPUT);
	pinMode(sensMid, INPUT);
}


int Scanner::roomScan()
{
  int left = digitalRead(sensLeft);
  int right = digitalRead(sensRight);
  int mid = digitalRead(sensMid);

  //REMEMBER!!!!!!
  //Sensors return ZERO (0) FOR TRUE (Flame found)
  //AND RETURN ONE (1) FOR FALSE (No Flame)
  
	//while (!right || !mid || !left)
      while (right == 0 || mid == 0 || left == 0)
      {
       //if (!mid && (right && left))
        if (mid == 0 && (right == 1 && left == 1))
        {
          return 1; //Flame is found (bool true) and needs no adjustment, it's centered
        }
        //else if (left && (!right))
        else if (left == 0 && right == 1)
        {
          //Robot must adjust leftwards
          return 2; //Flame found, adjust left
        }
        //else if (right && (!left))
        else if (right == 0 && left == 1)
        {
          //Robot must adjust rightwards
          return 3; 
        }

        //Re-reads sensor input to update currently existing flame position
        left = sensLeft;
        right = sensRight;
        mid = sensMid;
      }

  if (sensLeft && sensMid && sensRight)
  {
    return 0; //Fire not found, returning bool false value 
  }
  return 99; //Means an error was found and the program dropped out of the scope
}


/*
int Scanner::centering()
{
	//Takes in results from a scan and makes adjustments based on which sensors are returning
	//true or false
}

void Scanner::extinguish(int flmL, int flmR, int flmM)
{
	//Reads and double-checks the readings on each scanner, ensuring a centered target, then
	//calls a real extinguish function or simply activates the mechanism
}
*/
