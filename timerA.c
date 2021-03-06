#include "timerA.h"
#include "LEDDisplay.h"


#define NUMBER_OF_SAMPLES 8

extern volatile int samples_x[];
extern volatile int samples_y[];
extern volatile int samples_z[];

extern volatile int CurrentSample;
extern volatile unsigned int CurrentSampleIndex;
extern int gyro [];
extern int level [];
extern int period;
extern int x;
extern int y;
extern int z;

void ConfigureTimerA(void)
{
	//Stopping and clearing
	TA0CTL = (MC_0 | TACLR);
	TA0CTL |= (TASSEL_2 | MC_1);
	TA0CTL |= ID_0;

	TA1CTL = (MC_0 | TACLR);
	TA1CTL |= (TASSEL_2 | MC_1);
	TA1CTL |= ID_0;
	//TA0CTL |= TAIE;

	TA0CCR0 =  period;
	TA0CCTL0 |= CCIE;


	TA1CCR0 =  16000;
	TA1CCTL0 |= CCIE;
}




//controls the length of period
//once 1 pwm cycle ends, change CCR1 (up or down)
#pragma vector = TIMER1_A0_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void Timer1_A0_routine(void)
{
	ADC10CTL0 &= ~ENC;

	ADC10SA = (unsigned int) gyro;

	ADC10CTL0 |= ENC;
	ADC10CTL0 |= ADC10SC; // Start sampling and conversion
	while ((ADC10CTL1 & ADC10BUSY)) {}

	if (CurrentSampleIndex > NUMBER_OF_SAMPLES - 1) CurrentSampleIndex = 0;
	samples_x[CurrentSampleIndex] = gyro[2];
	samples_y[CurrentSampleIndex] = gyro[1];
	samples_z[CurrentSampleIndex] = gyro[0];

	CurrentSampleIndex++;
	filter();
}



//controls the length of each duty cycle and clock
#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG1 and TAIFG
__interrupt void Timer0_A0_routine(void)
{
	//this controls the brightness of 8 different LEDs
	//each led has a level of brightness and a name
	// for each LED, check its level and compare if the clock "cycle" is greater/less than the value. if less, stay on. if greater, turn off.

	volatile unsigned char LED = 0x00;
	static int cycle = 0;

	if(cycle >= 200)
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


void filter() 	//can be optimized
{
	//iterate over circular buffer
	int sum_x = 0;
	int sum_y = 0;
	int sum_z = 0;

	int i = 0;
	while (i < NUMBER_OF_SAMPLES) {
		sum_x += samples_x[i];
		sum_y += samples_y[i];
		sum_z += samples_z[i];
		i++;
	}
	x = sum_x >> 3;
	y = sum_y >> 3;
	z = sum_z >> 3;
}
