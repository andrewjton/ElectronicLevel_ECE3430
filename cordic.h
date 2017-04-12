#ifndef CORDIC_H
#define CORDIC_H

// Associated with 16-bit values, 8-bit fixed-point fractions.
#define CORDIC_1K 0x0000009B // decimal = 155
#define CORDIC_1K_X_EQUALS_Y 0x000000B5 // decimal = 181
#define MUL 256 // scaling multiplier
#define CORDIC_NTAB 16 // the number of angles

#define ATAN_HYP 1
#define SIN_COS 0

typedef struct {
	long x,y,angle;
} calculations;

// Function prototypes
void Cordic(calculations *calcs,char return_type);
/* 
 * This function uses the CORDIC algorithm to compute either the
 * hypotenuse/arctangent or the sine/cosine.  Which computations are performed
 * depends on the value of return_type: if (return_type == 0), the function
 * returns the sine/cosine; else it returns the hypotenuse/arctangent.
 *
 * To compute the hypotenuse/arctangent, the input arguments are (x,y). The
 * function computes the hypotenuse = sqrt(x^2+y^2) and atan(y/x), and
 * returns the results as angle = atan() and x = hypotenuse.
 *
 * To compute the sine/cosine, the input argument is angle, which represents the
 * angle with respect to the positive horizontal axis. The function computes
 * sin(angle) and cos(angle), and returns the values as y = sin(angle) and
 * x = cos(angle).
 */

#endif
