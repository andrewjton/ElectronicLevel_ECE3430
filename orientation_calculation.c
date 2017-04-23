#include "cordic.h"
#include "calibration.h"
#include "LEDDisplay.h"

LEDDirection getDirection()
{
	calculations calc;
	//use the multiplier 256
	calc.x = (getX() << 8);
	calc.y = (getY() << 8);

	if (calc.x > 0 && calc.y > 0) // positive and negative angles from x axis
	{
		Cordic(&calc,ATAN_HYP);
		if(calc.angle > 117280)  // if > 22.5 degrees, should be northeast
			return NE;
		if(calc.angle > 5760) //22.5 + 45 degrees
			return N;
	}5760


}
