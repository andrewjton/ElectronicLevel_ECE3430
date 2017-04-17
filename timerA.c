#include "timerA.h"
#include "LEDDisplay.h"


extern int level [];
extern int period;
extern int x;

void ConfigureTimerA(void)
{
	//Stopping and clearing
	TA0CTL = (MC_0 | TACLR);
	TA0CTL |= (TASSEL_2 | MC_1);
	TA0CTL |= ID_0;
	TA0CTL |= TAIE;

	TA0CCR0 =  period;
	TA0CCTL0 |= CCIE;


	TA0CCR1 =  100;
	TA0CCTL1 |= CCIE;
}




//controls the length of period
//once 1 pwm cycle ends, change CCR1 (up or down)
#pragma vector = TIMER0_A1_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void Timer0_A1_routine(void)
{
	x = ADC10MEM;
	ADC10CTL0 |= ADC10SC; // Start sampling and conversion
}



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

