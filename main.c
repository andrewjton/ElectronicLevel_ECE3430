#include <msp430.h> 

/*
 * main.c
 */

unsigned int period = 999;
unsigned int direction = 0;
unsigned int level [7];

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    InitializeLEDPortPins();
	ConfigureClockModule();
    ConfigureTimers(); //sets initial values for ccr1 (time on for LED) and ccr0 (timer)
	_enable_interrupts();

	while (1) {

	}

	return 0;
}
