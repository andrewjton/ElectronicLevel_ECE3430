#include "cordic.h"

const long cordic_ctab_degrees [CORDIC_NTAB] = { // Angle units = degrees
    0x00002D00, 0x00001A90, 0x00000E09, 0x00000720,
    0x00000393, 0x000001CA, 0x000000E5, 0x00000072,
    0x00000039, 0x0000001C, 0x0000000E, 0x00000007,
    0x00000003, 0x00000001, 0x00000000, 0x00000000 };

void Cordic(calculations *calcs, char return_type)
{
    int k, n = 16;
    long Xnew,Ynew,Anew,X,Y,A,cordic_ctab_value;
    
    // Initialize X, Y, and angle.
    X = calcs->x; Y = calcs->y; A = calcs->angle;
    
    for (k=0; k<n; ++k)
    {
        cordic_ctab_value = cordic_ctab_degrees[k];
        if (return_type == ATAN_HYP) {
            if (Y > 0) {
                Xnew = X + (Y>>k);
                Ynew = Y - (X>>k);
                Anew = A + cordic_ctab_value;
            }
            if (Y < 0) {
                Xnew = X - (Y>>k);
                Ynew = Y + (X>>k);
                Anew = A - cordic_ctab_value;                
            }
        }
        else {
            if (A > 0) {
                Xnew = X - (Y>>k);
                Ynew = Y + (X>>k);
                Anew = A - cordic_ctab_value;
            }
            if (A < 0) {
                Xnew = X + (Y>>k);
                Ynew = Y - (X>>k);
                Anew = A + cordic_ctab_value;
            }
        }
        X = Xnew; Y = Ynew; A = Anew;
    }
    calcs->x = X;
    calcs->y = Y;
    calcs->angle = A;
}
