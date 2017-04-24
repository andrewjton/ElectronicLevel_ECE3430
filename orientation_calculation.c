#include "cordic.h"
#include "calibration.h"
#include "LEDDisplay.h"

LEDDirection getDirection()
{
	calculations calc;
	//use the multiplier 256
	calc.x = (getX() << 8);
	calc.y = (getY() << 8);

	if (calc.x > 0 && calc.y > 0) // positive angles from x axis
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 117280)  // if > 22.5 degrees, should be northeast
			return N;
		if(calc.angle > 5760) //22.5 + 45 degrees
			return NE;
		return E;
	}

	if (calc.x > 0 && calc.y < 0) // negative angles from x axis
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 117280)  // if > 22.5 degrees, should be northeast
			return S;
		if(calc.angle > 5760) //22.5 + 45 degrees
			return SE;
		return E;
	}

	if (calc.x < 0 && calc.y > 0) // switching east to west
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 117280)  // if > 22.5 degrees, should be northeast
			return N;
		if(calc.angle > 5760) //22.5 + 45 degrees
			return NW;
		return W;
	}

	if (calc.x < 0 && calc.y < 0) // south/southwest
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 117280)  // if > 22.5 degrees, should be northeast
			return S;
		if(calc.angle > 5760) //22.5 + 45 degrees
			return SW;
		return W;
	}

	//This is for calculating the intensity of the tilt
	calc.y = (getZ() << 8);
	//calc.x is implicitly the hypotenuse
	Cordic(&calc,ATAN_HYP);
	//calc.angle is now theta
}
