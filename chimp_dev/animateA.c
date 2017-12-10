/*
 * This program will make the Chimp perform
 * the following movements:
 * 1) Head slightly upwards 45 degree
 * 2) Open mouth
 * 3) Close mouth
 * 4) Head all the way upward
 * 5) head back to slightly upwards 45 degrees
 * 6) Shake head left and right three times
 * 7) Center head back to looking straight forward
 *
 **/
#include "chimp_motors.h"
#include "chimp_def.h"

int main(void)
{
    int i;
    chimp_setup();
    
    head_UpD(45);
    mouth_UpD(90);
    mouth_UpD(0);
    head_UpD(0);
    head_UpD(45); 
    
    for(i=0;i<3;i++)
    {
        head_LR(-45);
        head_LR(45);
    }
    head_LR(0); 

    return 0;

}

