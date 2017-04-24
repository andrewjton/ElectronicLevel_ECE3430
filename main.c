#include <msp430.h> 
#include "LEDDisplay.h"
#include "spi.h"
#include "timerA.h"
#include "cordic.h"
#include "ADC.h"
#include "pushbutton.h"
#include "calibration.h"
#include "orientation_calculation.h"
/*
 * main.c
 */

volatile unsigned int period = 8000;
volatile unsigned int direction = 0;
volatile unsigned int level[8] = {10,1,0,0,0,1,10,30};
volatile unsigned int gyro[3];

volatile unsigned int x;
volatile unsigned int y;
volatile unsigned int z;
volatile int samples_x[8];
volatile int samples_y[8];
volatile int samples_z[8];

volatile int rangex[2];
volatile int rangey[2];
volatile int rangez[2];
volatile int offsets[3]; // zero point offsets


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

	//initialize to pointing north
	setLevelLEDs(No);

	simpleCalibration();


	while (1) {
		setLevelLEDs(getDirection());

	}
}

void ConfigureClockModule(void)
{
    // Configure Digitally Controlled Oscillator (DCO) for 1 MHz using factory
    // calibrations.
	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
