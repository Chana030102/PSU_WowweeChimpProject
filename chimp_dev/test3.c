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

