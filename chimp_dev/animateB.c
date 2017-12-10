/*
 * This program will make the Chimp perform
 * the following movements:
 * 1) Move eyes left and right twice
 * 2) Center eyes to look forward
 * 3) Move eyebrows up and down twice
 * 4) Open and close moouth
 *
 **/
#include "chimp_motors.h"
#include "chimp_def.h"

int main(void)
{
    int i;
    chimp_setup();

    for (i=0; i<2; i++)
    {
        eyes_LR(-90);
        eyes_LR(90);
    }
    eyes_LR(0);
    
    for (i=0; i <2; i++)
    {
        brows_UpD(90);
        brows_UpD(0);
    }

    mouth_UpD(90);
    mouth_UpD(0);

    return 0;    
}
