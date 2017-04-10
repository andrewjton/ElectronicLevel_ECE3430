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
void updateDisplay(unsigned char tens, unsigned char ones)
{
	SPISendByte(ones);
	SPISendByte(tens);

	RISE_X_LATCH;
	FALL_X_LATCH;
}

char convertToDisplay(int value)
{
	// this is 0
	char digit = 0x3f;
	switch(value)
	{
		case 1:
			digit = 0x06;
			break;
		case 2:
			digit = 0x5b;
			break;
		case 3:
			digit = 0x4f;
			break;
		case 4:
			digit = 0x66;
			break;
		case 5:
			digit = 0x6d;
			break;
		case 6:
			digit = 0x7d;
			break;
		case 7:
			digit = 0x07;
			break;
		case 8:
			digit = 0x7f;
			break;
		case 9:
			digit = 0x67;
			break;
		default:
			digit = 0x00;
	}
	return digit;
}

void sendCount(int digit)
{
	//volatile int number = digit;
	int tens = digit/10;
	int ones = digit - (10*tens);
	//sends the digits with the proper hex encodings
	updateDisplay(convertToDisplay(tens),convertToDisplay(ones));
}

