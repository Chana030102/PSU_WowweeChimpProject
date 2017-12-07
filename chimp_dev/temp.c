#include "chimp_motors.h"
#include "chimp_def.h"

int main(void)
{
    chimp_setup();

    WRITE_LOW(M_ENABLE);
    WRITE_LOW(M_MOUTH_O);
    WRITE_LOW(M_MOUTH_C);
    WRITE_LOW(M_EYES_U);
    WRITE_LOW(M_EYES_D);
    WRITE_LOW(M_EYES_L);
    WRITE_LOW(M_EYES_R);
    WRITE_LOW(M_BROWS_U);
    WRITE_LOW(M_BROWS_D);
    WRITE_LOW(M_HEAD_U);
    WRITE_LOW(M_HEAD_D);
    WRITE_LOW(M_HEAD_L);
    WRITE_LOW(M_HEAD_R);
    WRITE_LOW(M_NOSE_U);
    WRITE_LOW(M_NOSE_D);

    return 0;
}
