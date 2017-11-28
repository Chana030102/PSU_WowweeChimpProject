/*
 * Test program to try out wiringPi functions
 **/
#include <stdio.h>
#include <wiringPi.h>

#define PIN 26

int main(void)
{
    int i;

    wiringPiSetupGpio(); // Use BCM GPIO numbering
    pinMode(PIN, OUTPUT);
    
    for(i=0;i<3;i++)
    {
        digitalWrite(PIN,HIGH);
        delay(500);
        digitalWrite(PIN,LOW);
        delay(500);
    }
    return 0;
}

