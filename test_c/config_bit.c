/* 
 * Test output results of setconfig_bits function
 */
#include "mcp3008_rpi3.h"
#include <stdio.h>

int main(void)
{
    int bits[5];
    int i;
    
    for(i=0;i<5;i++)
        bits[i] = 0;

    mcp3008_setconfig_bits(bits,1,2);
    
    printf("Config bits: ");
    for(i=0;i<5;i++)
        printf("%d ",bits[i]);
    printf("\n");
    return 0;
}
