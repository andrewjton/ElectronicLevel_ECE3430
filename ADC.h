#ifndef ADC_H
#define ADC_H
#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      ADC10 Analog Input
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define ADC10_ANALOG_INPUT_BIT		BIT0
#define ADC10_ANALOG_INPUT_SELECT	INCH_0

// Prototypes
void ConfigureADC(void);

#endif
