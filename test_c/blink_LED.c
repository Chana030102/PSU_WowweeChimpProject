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
    gpio_rpi3_set(LED, OUT);
    gpio_rpi3_write(LED,1);
    sleep(2);
    gpio_rpi3_write(LED,0);
    gpio_rpi3_cleanup(); 
    return 0;
}
