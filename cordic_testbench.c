#include <msp430.h>
#include <math.h>
#include "cordic.h"

#define TEST_SIZE 5
#define CORDIC_GAIN 0.607252935103139
#define CORDIC_GAIN_X_EQUALS_Y (float) (sqrt(2)/2)
#define PI 3.1415926536897932384626

// Local prototypes
void ConfigureClockModule();

extern const long cordic_ctab_degrees[CORDIC_NTAB];

//void main()
//{
//	float test_angles[TEST_SIZE] = {26.565,45.0, 0.0, 0.0, 0.0};
//	float test_x[TEST_SIZE] = {100, 200, -200, -100, 100};
//	float test_y[TEST_SIZE] = {100, 100, 100, -200, -200};
//	unsigned int i;
//    volatile float sine, cosine, angle, hypotenuse;
//    calculations calcs;
//
//    // Stop watchdog timer, and configure clock module.
//	WDTCTL = WDTPW + WDTHOLD;
//    ConfigureClockModule();
//
//    // First, test the CORDIC function for a given angle, to compute the sine and cosine.
//	hypotenuse = 0;
//	angle = 0;
//    for (i = 0; i < TEST_SIZE; i++) {
//    	calcs.angle = MUL*test_angles[i]; calcs.x = CORDIC_1K; calcs.y = 0;
//
//    	// X is initialized to equal MUL*CORDIC_GAIN, which equals 0x9B (155 decimal), for
//    	// MUL = 256 and CORDIC_GAIN = 0.607252935103139.  However, if angle = 45 (degrees),
//    	// then the CORDIC_GAIN = sqrt(2)/2, which implies X = 0xB5 (181 decimal).
//    	if (calcs.angle == cordic_ctab_degrees[0]) { // calcs.angle = 45 degrees
//    		calcs.x = CORDIC_1K_X_EQUALS_Y;
//    	}
//    	Cordic((calculations *)&calcs,SIN_COS);
//    	cosine = ((float) calcs.x)/MUL;
//    	sine = ((float) calcs.y)/MUL;
//    	_nop();
//    }
//
//    // Now, test the CORDIC function for given values of x and y, to compute the
//    // atan(y/x) and the hypotenuse.
//    sine = 0;
//    cosine = 0;
//    for (i = 0; i < TEST_SIZE; i++) {
//    	if (test_x[i] >= 0) { // first quadrant and fourth quadrant
//    		calcs.x = MUL*test_x[i]; calcs.y = MUL*test_y[i]; calcs.angle = 0;
//    		Cordic((calculations *)&calcs,ATAN_HYP);
//    		angle = ((float) calcs.angle)/MUL;
//    	}
//    	else if (test_x[i] < 0 && test_y[i] >= 0) { // second quadrant
//    		calcs.x = -1.0*MUL*test_x[i]; calcs.y = MUL*test_y[i]; calcs.angle = 0;
//    		Cordic((calculations *)&calcs,ATAN_HYP);
//    		angle = 180.0 - ((float) calcs.angle)/MUL;
//    	}
//    	else if (test_x[i] < 0 && test_y[i] < 0) { // third quadrant
//    		calcs.x = -1.0*MUL*test_x[i]; calcs.y = -1.0*MUL*test_y[i]; calcs.angle = 0;
//    		Cordic((calculations *)&calcs,ATAN_HYP);
//    		angle = ((float) calcs.angle)/MUL - 180.0;
//    	}
//
//    	// X is adjusted by the CORDIC_GAIN, which equals 0x9B (155 decimal), for
//    	// MUL = 256 and CORDIC_GAIN = 0.607252935103139.  However, if X = Y,
//    	// then the CORDIC_GAIN = sqrt(2)/2.
//    	if (test_x[i] == test_y[i]) {
//    		hypotenuse = ((float) calcs.x)*CORDIC_GAIN_X_EQUALS_Y/MUL;
//    	}
//    	else {
//    		hypotenuse = ((float) calcs.x)*CORDIC_GAIN/MUL;
//    	}
//    	_nop();
//    }
//}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) for 16 MHz using factory calibrations
	DCOCTL  = CALDCO_16MHZ;
	BCSCTL1 = CALBC1_16MHZ;
}
