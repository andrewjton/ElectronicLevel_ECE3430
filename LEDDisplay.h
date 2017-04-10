/*
 * LEDDisplay.h
 *
 *  Created on: Mar 22, 2017
 *      Author: syedm_000
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * X latch
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P2.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define X_LATCH_BIT					BIT0
#define X_LATCH_PORT				P2OUT
#define X_LATCH_DDR					P2DIR
#define SET_X_LATCH_AS_AN_OUTPUT	X_LATCH_DDR |= X_LATCH_BIT

#define RISE_X_LATCH				X_LATCH_PORT |= X_LATCH_BIT
#define FALL_X_LATCH				X_LATCH_PORT &= (~X_LATCH_BIT)

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * BLANK
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.4
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define BLANK_BIT					BIT4
#define BLANK_PORT					P1OUT
#define BLANK_DDR					P1DIR
#define SET_BLANK_AS_AN_OUTPUT	BLANK_DDR |= BLANK_BIT

#define RISE_BLANK					BLANK_PORT |= BLANK_BIT
#define FALL_BLANK					BLANK_PORT &= (~BLANK_BIT)

void initializeDisplay(void);

//Displays the value into base 10 representation on the display
void sendCount(int digit);

void milestone2();

#endif /* LEDDISPLAY_H_ */
