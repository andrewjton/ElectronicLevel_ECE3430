/*
 * calibration.h
 *
 *  Created on: Apr 19, 2017
 *      Author: syedm_000
 */
#include "calibration.h"

extern unsigned int x;
extern unsigned int y;
extern unsigned int z;

extern int rangex[2];
extern int rangey[2];
extern int rangez[2];
extern int offsets[3]; // zero point offsets


void calibrationRoutine()
{
	//getting min x
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	rangex[0] = x;
	//10/4 of a second?
	_delay_cycles(2500000);

	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangex[1] = x;
	_delay_cycles(2500000);


	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangey[0] = y;
	_delay_cycles(2500000);

	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangey[1] = y;
	_delay_cycles(2500000);

	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangez[0] = z;
	_delay_cycles(2500000);
	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	while(!(PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));

	rangez[1] = z;
	_delay_cycles(2500000);

	//getting the level
	//while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT));
	offsets[0] = ((rangex[0] + rangex[1])>>1);
	offsets[1] = ((rangey[0] + rangey[1])>>1);
	offsets[2] = ((rangez[0] + rangez[1])>>1);
	_delay_cycles(2500000);
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
