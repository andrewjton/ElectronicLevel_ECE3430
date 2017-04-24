#include "cordic.h"
#include "calibration.h"
#include "LEDDisplay.h"

LEDDirection getDirection()
{
	volatile int debug = 0;
	LEDDirection retVal = No;

	calculations calc;
	//use the multiplier 256
	calc.x = (getX() << 8);
	calc.y = (getY() << 8);

	//calc.x = (10<<8); calc.y = (-1<<8);
	calc.angle = 0;

	if (calc.x >= 0 && calc.y <= 0) // positive angles from x axis
	{
		calc.y = -calc.y;
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 17280)  // if > 22.5 degrees, should be northeast
			retVal = E;
		else if(calc.angle > 5760) //22.5  degrees
			retVal = NE;
		else retVal = No;
	}
	if (calc.x < 0 && calc.y < 0) // negative angles from x axis
	{
		calc.y = -calc.y;
		calc.x = -calc.x;
		Cordic(&calc,ATAN_HYP);
		debug = 1;
		if(calc.angle > 17280)  // if > 22.5 degrees, should be northeast
			retVal = E;
		else if(calc.angle > 5760) //22.5 + 45 degrees
			retVal = SE;
		else retVal = S;
	}
	if (calc.x > 0 && calc.y > 0) // switching east to west
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 17280)  // if > 22.5 degrees, should be northeast
			retVal = W;
		else if(calc.angle > 5760) //22.5 + 45 degrees
			retVal = NW;
		else retVal = No;
	}

	if (calc.x < 0 && calc.y > 0) // south/southwest
	{
		calc.x = -calc.x;

		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 17280)  // if > 22.5 degrees, should be northeast
			retVal = W;
		else if(calc.angle > 5760) //22.5 + 45 degrees
			retVal = SW;
		else retVal = S;
	}
//	else
//	{
//		Cordic(&calc,ATAN_HYP);
//	}
	//This is for calculating the intensity of the tilt
	//need atan(hypotenuse/z)
	calc.y = calc.x;
	calc.x = (getZ() << 8);
	if(calc.x < 0)
		calc.x = -calc.x;
	//calc.x is implicitly the hypotenuse after the previous operations
	calc.angle = 0;
	Cordic(&calc,ATAN_HYP);
	if(calc.angle < 2000)
		retVal = All;
	//calc.angle is now theta

	return retVal;
}
