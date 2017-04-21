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
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
		_nop();
	}
	rangex[0] = 10;
	//10/4 of a second?
	_delay_cycles(2500000);

	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
		_nop();

	}
	rangex[1] = x;
	_delay_cycles(2500000);


	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
		_nop();

	}
	rangey[0] = y;
	_delay_cycles(25000);


	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
	}
	rangey[1] = y;
	_delay_cycles(25000);


	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
	}
	rangez[0] = z;
	_delay_cycles(25000);

	//getting max
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{
	}
	rangez[1] = z;
	_delay_cycles(25000);


	//getting the level
	while((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT) == PUSHBUTTON_BIT)
	{

	}
	offsets[0] = x;
	offsets[1] = y;
	offsets[2] = z;
	_delay_cycles(25000);

}


