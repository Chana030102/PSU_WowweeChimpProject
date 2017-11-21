/*
 * Test progriam to try out wiringPi functions
 * for the MCP3008
 **/
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define BASE 300

int main(void)
{
    int i;
    int value[8];

    wiringPiSetupGpio(); // Use BCM GPIO numbering

    mcp3004Setup(BASE,0);
    printf("|  00  |  01  |  02  |  03  |  04  |  05  |  06  |  07  |\n");

    while(1)
    {
    for(i=0;i<8;i++)
        value[i] = analogRead(BASE+i);
    
    printf("| % 4d | % 4d | % 4d | % 4d | % 4d | % 4d | % 4d | % 4d |\n",
            value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7]);

    sleep(1);
    }
//    printf("Got: %d\n",analogRead(100));
    return 0;
}
