#include <msp430.h> 
#include "LEDDisplay.h"
#include "spi.h"
#include "timerA.h"
#include "cordic.h"
#include "ADC.h"

/*
 * main.c
 */

volatile unsigned int period = 9;
volatile unsigned int direction = 0;
volatile unsigned int level [8] = {10,1,0,0,0,1,10,30};

volatile unsigned int x;

void ConfigureClockModule();

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	ConfigureClockModule();
	ConfigureADC();

	initializeDisplay();
    ConfigureTimerA(); //sets initial values for ccr1 (time on for LED) and ccr0 (timer)
	_enable_interrupts();

	while (1) {


		//add buffer later? perhaps in ISR
	}

	return 0;
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) for 1 MHz using factory
    // calibrations.
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
