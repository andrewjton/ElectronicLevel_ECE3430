/*
 * LEDDisplay.c
 *
 *  Created on: Mar 22, 2017
 *      Author: syedm_000
 */

#include "LEDDisplay.h"
#include "spi.h"

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

//not really used
char convertToDisplay(LEDDirection d)
{
	// this is 0
	char digit = 0x3f;
	switch(d)
	{
		case No:
			digit = 0x06;
			break;
		case NE:
			digit = 0x5b;
			break;
		case E:
			digit = 0x4f;
			break;
		case SE:
			digit = 0x66;
			break;
		case S:
			digit = 0x6d;
			break;
		case SW:
			digit = 0x07;
			break;
		case W:
			digit = 0x7f;
			break;
		case NW:
			digit = 0x67;
			break;
		default:
			digit = 0x00;
	}
	return digit;
}
