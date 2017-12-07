#include "chimp_motors.h"
#include "chimp_def.h"

int main(void)
{
    chimp_setup();

    /*
    digitalWrite(M_ENABLE,HIGH);
    digitalWrite(M_HEAD_L,HIGH);
    digitalWrite(M_HEAD_R,LOW);
    delay(1000);
    digitalWrite(M_HEAD_L,LOW);
    digitalWrite(M_ENABLE,LOW);
    */

    WRITE_HIGH(M_ENABLE);
    WRITE_LOW(M_HEAD_L);
    WRITE_LOW(M_HEAD_R);
    while (1)
    {
        WRITE_HIGH(M_HEAD_L);
        delay(1000);
        WRITE_LOW(M_HEAD_L);
        WRITE_HIGH(M_HEAD_R);
        delay(1000);
        WRITE_LOW(M_HEAD_R);
    }

}

