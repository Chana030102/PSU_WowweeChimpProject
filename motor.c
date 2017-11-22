/*
 *
 **/
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define BASE 200
// GPIO pins for motors
#define M_ENABLE   26
#define M_MOUTH_UP 2
#define M_MOUTH_D  3

#define L_MOUTH_c 370
#define L_MOUTH_o 530
// prototype
void mouth_close(void);
void mouth_open(void);

int main(void)
{
    int head;

    wiringPiSetupGpio();
    mcp3004Setup(BASE,0); 
    pinMode(M_MOUTH_UP, OUTPUT);
    pinMode(M_MOUTH_D, OUTPUT);
    pinMode(M_ENABLE, OUTPUT);
   
    digitalWrite(M_ENABLE,HIGH); 
    mouth_close();

    while(1)
    {
        head = analogRead(BASE);
        if(head <= L_MOUTH_c)
            mouth_open();
        
        if(head >= L_MOUTH_o)
            mouth_close();       
    } 
    return 0;
}

void mouth_close(void)
{
    digitalWrite(M_MOUTH_UP, HIGH);
    digitalWrite(M_MOUTH_D , LOW);
}

void mouth_open(void)
{
    digitalWrite(M_MOUTH_UP, LOW);
    digitalWrite(M_MOUTH_D , HIGH);
}

