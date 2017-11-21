/*
 * Example to test GPIO_RPi3.h functions.
 * Blink an LED
 */
#include "gpio_rpi3.h"
#include <stdio.h>
#include <unistd.h>

#define LED 2

int main(void)
{
    printf("Setup LED pin as output.\n");
    gpio_rpi3_set(LED, "out");

    printf("Write HIGH to LED pin.\n");
    gpio_rpi3_write(LED,1);
    sleep(2);

    printf("Write LOW to LED pin.\n");
    gpio_rpi3_write(LED,0);
    
    sleep(1);
    printf("Cleanup GPIO pins\n");
    gpio_rpi3_rm(LED); 
    return 0;
}
