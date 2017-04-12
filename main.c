#include <msp430.h> 

/*
 * main.c
 */

unsigned int period = 999;
unsigned int direction = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    InitializeLEDPortPins();

	return 0;
}
