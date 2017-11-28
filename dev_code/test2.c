#include "chimp_motors.h"

int main(void)
{
    chimp_setup();

    digitalWrite(M_ENABLE,HIGH);
    digitalWrite(M_HEAD_U,HIGH);
    digitalWrite(M_HEAD_D,LOW);
    delay(1000);
    digitalWrite(M_HEAD_U,LOW);
    digitalWrite(M_ENABLE,LOW);

}

