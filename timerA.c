#include "timerA.h"
#include "LEDDisplay.h"


extern int level [];
extern int period;

void ConfigureTimerA(void)
{
	//Stopping and clearing
	TA0CTL = (MC_0 | TACLR);
	//Setting the timer as SMCLK and in up
	TA0CTL |= (TASSEL_2 | MC_1);

	//Setting the timer to divide by 4
	TA0CTL |= ID_0;
	//16 Mhz

	TA0CCR0 =  period;

	// enable the interrupts
	TA0CCTL0 |= CCIE;
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
#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG1 and TAIFG
__interrupt void Timer0_A0_routine(void)
{
	//this controls the brightness of 8 different LED ports.
	//each led has a magnitude of brightness and a name
	// for each LED, check its magnitude and compare if the clock is greater/less than the value. if less, stay on. if greater, turn off.

	volatile unsigned char LED = 0x00;
	static int cycle = 0;

	if(cycle >= 30)
	{
		cycle = 0;
	}

	int i = 0;
	for (; i < 8; i++) {
		if (cycle < level[i])
			LED |= (0x01 << i);
	}
	updateDisplay(LED);

	cycle++;
}

