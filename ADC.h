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

#define LED1 1
#define LED1_BIT				BIT0
#define LED1_PORT				P1OUT
#define LED1_DDR				P1DIR
#define SET_LED1_AS_AN_OUTPUT	LED1_DDR |= LED1_BIT
#define TURN_ON_LED1			LED1_PORT |= LED1_BIT
#define TURN_OFF_LED1			LED1_PORT &= ~LED1_BIT
#define TOGGLE_LED1				LED1_PORT ^= LED1_BIT

#define LED1 1
#define LED1_BIT				BIT0
#define LED1_PORT				P1OUT
#define LED1_DDR				P1DIR
#define SET_LED1_AS_AN_OUTPUT	LED1_DDR |= LED1_BIT
#define TURN_ON_LED1			LED1_PORT |= LED1_BIT
#define TURN_OFF_LED1			LED1_PORT &= ~LED1_BIT
#define TOGGLE_LED1				LED1_PORT ^= LED1_BIT




// Prototypes
void ConfigureADC(void);

#endif
