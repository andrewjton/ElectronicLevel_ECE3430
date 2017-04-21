#include <msp430.h> 
#include "LEDDisplay.h"
#include "spi.h"
#include "timerA.h"
#include "cordic.h"
#include "ADC.h"
#include "pushbutton.h"

/*
 * main.c
 */

volatile unsigned int period = 500;
volatile unsigned int direction = 0;
volatile unsigned int level[8] = {10,1,0,0,0,1,10,30};
volatile unsigned int gyro[3];

volatile unsigned int x;
volatile unsigned int y;
volatile unsigned int z;
volatile int samples_x[8];
volatile int samples_y[8];
volatile int samples_z[8];

volatile int CurrentSample;
volatile unsigned int CurrentSampleIndex;

void ConfigureClockModule();

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	ConfigureClockModule();
	ConfigureADC();

	InitializePushButtonPortPin();
	initializeDisplay();
    ConfigureTimerA(); //sets initial values for ccr1 (time on for LED) and ccr0 (timer)
	_enable_interrupts();

	while (1) {
		modifyLED(S, 30 );

//
//		ADC10SA = gyro;
//
//			ADC10CTL0 &= ~ENC;
//			ADC10CTL0 |= ENC;
//			ADC10CTL0 |= ADC10SC; // Start sampling and conversion

//			while ((ADC10CTL1 & ADC10BUSY)) {
//
//				x = 2;
//			}
//
//			ADC10CTL0 &= ~ENC;
//			ADC10CTL0 |= ENC;
//				ADC10CTL0 |= ADC10SC; // Start sampling and conversion
//
//				while ((ADC10CTL1 & ADC10BUSY)) {
//					y = 2;
//				}
//
//				ADC10CTL0 &= ~ENC;
//				ADC10CTL0 |= ENC;
//					ADC10CTL0 |= ADC10SC; // Start sampling and conversion
//
//					while ((ADC10CTL1 & ADC10BUSY)) {
//						z = 2;
//					}





//		if((PUSHBUTTON_PORT_IN & PUSHBUTTON_BIT)) {
//
//		}
//		else {
//			_nop();
//		}
//		int i = 7;
//		for (; i >= 0; i--) {
//			level[i] = 30;
//			level[(i - 1)%8] = 10;
//			level[(i+1)%8] = 10;
//			level[(i+2)%8] = 1;
//		    level[(i - 2)%8] = 1;
//		}
		//add buffer later? perhaps in ISR
	}
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) for 1 MHz using factory
    // calibrations.
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
