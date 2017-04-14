#include "timerA.h"
#include "LEDDisplay.h"


extern int [] level;

void ConfigureTimers(void)
{
	TA0CTL	=	(MC_0	|	TACLR);	//stops timer and clears it
	TA0CTL	|=	(TASSEL_2	|	MC_1); ///sets timer and begins it counting up. smclk setting
	TA0CCR0 = period; //assign value to compare/capture register
	TA0CCTL0	|=	CCIE;	//enables capture/compare control register
	TA0CCTL1	|=	CCIE;	//enables capture/compare control register
	TA0CTL	|=	TAIE; // TAIFG

	TA0CCR1 = 100; // CHANGE THIS INITIAL VALUE EVENTUALLY!
}




//controls the length of period
//once 1 pwm cycle ends, change CCR1 (up or down)
//#pragma vector = TIMER0_A0_VECTOR
//// Interrupt service routine for CCIFG0
//__interrupt void Timer0_A0_routine(void)
//{
//	//static int direction = 1; //static variable
//	if (TA0CCR1 == period) direction = 0;
//	if (TA0CCR1 == 90) direction = 1;
//
//	if (direction == 1) TA0CCR1++;
//	else if (direction == 0) TA0CCR1--;
//}



//controls the length of each duty cycle and clock
#pragma vector = TIMER0_A1_VECTOR
// Interrupt service routine for CCIFG1 and TAIFG
__interrupt void Timer0_A1_routine(void)
{
	//this controls the brightness of 8 different LED ports.
	//each led has a magnitude of brightness and a name
	// for each LED, check its magnitude and compare if the clock is greater/less than the value. if less, stay on. if greater, turn off.

	unsigned char LED;
	int i = 0;
	for (; i < 8; i++) {
		if (cycle >= level[i]) LED |= 0x01;
		LED << 1;
	}
	updateDisplay(LEDs);
}

