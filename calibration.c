/*
 * calibration.h
 *
 *  Created on: Apr 19, 2017
 *      Author: syedm_000
 */
#include "calibration.h"
#include "LEDDisplay.h"

extern unsigned int x;
extern unsigned int y;
extern unsigned int z;

extern int rangex[2];
extern int rangey[2];
extern int rangez[2];
extern int offsets[3]; // zero point offsets


void calibrationRoutine()
{
	modifyLED(No,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	rangex[0] = x;
	_delay_cycles(2500000);

	modifyLED(S,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangex[1] = x;
	_delay_cycles(2500000);

	modifyLED(W,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangey[0] = y;
	_delay_cycles(2500000);

	modifyLED(E,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangey[1] = y;
	_delay_cycles(2500000);

	modifyLED(ZP,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangez[0] = z;
	_delay_cycles(2500000);

	modifyLED(ZN,200);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangez[1] = z;
	_delay_cycles(2500000);

	//averaging and getting the offset
	offsets[0] = ((rangex[0] + rangex[1])>>1);
	offsets[1] = ((rangey[0] + rangey[1])>>1);
	offsets[2] = ((rangez[0] + rangez[1])>>1);
}

//all we really need are the x,y offsets from 0
//put device on level surface, then push the button
void simpleCalibration()
{
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	offsets[0] = x;
	offsets[1] = y;
	rangez[0] = z;

	_delay_cycles(250000);
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	rangez[1] = z; // this is the max or min of z (if held upside down)
	offsets[2] = ((rangez[0] + rangez[1]) >> 1);

}
//subroutines for getting the calibrated cartesian values
int getX()
{return (x - offsets[0]);}
int getY()
{return (y - offsets[1]);}
int getZ()
{return (offsets[2] - z);}
