/*
 *
 **/
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

// arbitrary base for wiringPi to assign
// pins for use. 
#define BASE 200 
#define 
#define SPI_CHAN 0 

// GPIO pins for motors
#define M_ENABLE 26
#define M_MOUTH_O 2
#define M_MOUTH_C 3

// Limit values for motor positions
#define L_MOUTH_c 370
#define L_MOUTH_o 530

// Prototypes
int mouth_close(int position);
int mouth_open(int position);

int mouth_close(int position)
{
    int current = analogRead

    if(position < L_MOUTH_c && position > L_MOUTH_o)
    {
        fprintf(stderr,"That is out of range.
                Give value between %d and %d.\n",L_MOUTH_c,L_MOUTH_o);
        return -1;
    }
    
    

}
