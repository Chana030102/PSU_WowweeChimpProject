// Move head up or down based of degrees given
#include "chimp_motors.h"

int main(void)
{
    int i;
    int position[5] = {0,90,-90,45,30};
    chimp_setup();

    for(i=0;i<5;i++)
    {
        head_UpD(position[i]);
        delay(500);
    }
    
    return 0;
}
