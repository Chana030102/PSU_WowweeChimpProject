#include "chimp_motors.h"

int main(void)
{
    chimp_setup();
    head_position(0,0);
    head_position(-90,-90);
    head_position(90,90);
    
    return 0;
}
