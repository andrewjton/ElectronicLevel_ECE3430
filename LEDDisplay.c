/*
 * LEDDisplay.c
 *
 *  Created on: Mar 22, 2017
 *      Author: syedm_000
 */

#include "LEDDisplay.h"
#include "spi.h"


extern unsigned int level[];
extern unsigned int intensity;

void initializeDisplay()
{
	InitializeSPI();

	SET_X_LATCH_AS_AN_OUTPUT;
	SET_BLANK_AS_AN_OUTPUT;

	FALL_BLANK; // Just keep the LEDs on
	FALL_X_LATCH;
}

//sends raw bits and triggers latch
void updateDisplay(unsigned char led)
{
	SPISendByte(led);

	RISE_X_LATCH;
	FALL_X_LATCH;
}

// changed enum order to directly map to LED array
void modifyLED(LEDDirection dir, int intensity ) {

int i = 0;
	for(i = 0; i < 8; i++)
		{
			level[i] = 0;
		}

	level[dir] = intensity;
	switch (dir) {
	case No:
		level[7] = intensity;
		break;
	case NE:
		level[6] = intensity;
		break;
	case E:
		level[5] = intensity;
		break;
	case SE:
		level[4] = intensity;
		break;
	case S:
		level[3] = intensity;
		break;
	case SW:
		level[2] = intensity;
		break;
	case W:
		level[1] = intensity;
		break;
	case NW:
		level[0] = intensity;
		break;
	default:
		break;
	}
	if(dir == All)
		{
			for(i = 0; i < 8; i++)
					{
						level[i] = 5;
					}
		}
	if(dir == ZP)
	{
		for(i = 1; i < 8; i+=2)
		{
			level[i]= intensity;
		}
	}
	if(dir == ZN)
	{
		for(i = 0; i < 8; i+=2)
		{
			level[i]= intensity;
		}
	}
}

//the directions wrap around
void setLevelLEDs(LEDDirection dir)
{
	int i =0;
	for(i = 0; i < 8; i++)
	{
		level[i] = 0;
	}

	int direction = dir;
	level[dir] = 5*intensity; //closest direction

	direction++;
	if(direction > 7)
		direction = 0;
	level[direction] = 20; //1 LED counter clockwise
	direction++;
		if(direction > 7)
			direction = 0;
		level[direction] = 5; //2 LED counter clockwise

	direction = dir;
	direction--;
		if(direction < 0)
			direction = 7;
	level[direction] = 20; //1 LED clockwise
	direction--;
		if(direction < 0)
			direction = 7;
		level[direction] = 5; //2 LED clockwise

	if(dir == All)
		{
			for(i = 0; i < 8; i++)
					{
						level[i] = 30;
					}
		}
	if(dir == None)
	{
	for(i = 0; i < 8; i++)
		{
			level[i] = 0;
		}
	}
}

