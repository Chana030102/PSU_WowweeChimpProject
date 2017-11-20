/*
   GPIO_RPi3.h (C) Aaron Chan
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
==================================================================
 *  GPIO library developed for Raspberry Pi 3
 *  Tested on Raspberry Pi 3 Model B Vi 2 
 *
 * NOTE: GPIO pins are BCM numbering, not physical pin numbering.
 *
 * Raspberry Pi 3 GPIO pins number from 2 --> 27
 */
#include <stdio.h>
#include <string.h>

#define OUT "out"
#define IN "in"
/*============ GLOBALS ================*/
const char PATH[]          = "/sys/class/gpio/gpio";
const char GPIO_ADD_PATH[] = "/sys/class/gpio/export";
const char GPIO_RM_PATH[]  = "/sys/class/gpio/unexport";

/*============ PROTOTYPES ============*/
int gpio_rpi3_setup(void); 
int gpio_rpi3_set(int pin, char *direction);
int gpio_rpi3_write(int pin, int value);
int gpio_rpi3_read(int pin);

/**
 * gpio_rpi3_setup - setup all GPIO pins and initialize as inputs
 *
 * File access method of using GPIO pins.
 * GPIO pins are initialized as inputs to avoid writing to things
 * that it isn't supposed to.
 *
 * return -1 when fail to open GPIO_ADD_PATH
 * return 0 when successful
 **/
int gpio_rpi3_setup(void)
{
    FILE *f;
 
    if(!(f = fopen(GPIO_ADD_PATH,"w")))
    {
        fprintf(stderr,"Failed to open %s\n",GPIO_ADD_PATH);
        return -1;
    }

    for(int i = 2; i< 28; i++)
    {
        fprintf(f,GPIO_ADD_PATH,"%d",i);
        gpio_rpi3_set(i,"in");
    }

    fclose(f);
    return 0;        
}

/**
 * gpio_rpi3_set - set GPIO pin as input or ouptput
 * @pin: GPIO pin 
 * @direction: "out" or "in"
 *
 * return -1 upon invalid input or failure to open files
 * return 0 upon success
 **/
int gpio_rpi3_set(int pin, char *direction)
{
    FILE *f, *g;
    char pinpath[40];

    // Test for invalid inputs
    if(pin < 2 || pin > 27)
    {
        fprintf(stderr,"Invalid GPIO pin number of %d\n",pin);
        return -1;
    }

    if(strcmp(direction, "in")!=0 || strcmp(direction,"out")!=0)
    {
        fprintf(stderr,"Invalid direction of %s\n",direction);
        return -1;
    }
    sprintf(pinpath,"%s%d/direction",PATH,pin); // concatenate for GPIO# directory path

    // Test for GPIO# directory. Make if not there
    if(!(g = fopen(pinpath,"w")))
    {
        if(!(f = fopen(GPIO_ADD_PATH,"w")))
        {
            fprintf(stderr,"Failed to open %s\n",GPIO_ADD_PATH);
            return -1;
        }

        fprintf(f,"%d",pin);
        fclose(f);
        
        g = fopen(pinpath,"w");
    }
    
    fprintf(g,"%s",direction);
    fclose(g);
    return 0;
}

/**
 * gpio_rpi3_write - output HIGH or LOW to GPIO pin
 * @pin: GPIO pin
 * @value: 1 or 0
 * 
 * return -1 if invalid input
 * return 0 upon success
 **/
int gpio_rpi3_write(int pin, int value)
{
    FILE *f;
    char pinpath[40];
     sprintf(pinpath,"%s%d/value",PATH,pin); // concatenate for GPIO# director path

    // Test for invalid inputs
    if(pin < 2 || pin > 27)
    {
        fprintf(stderr,"Invalid GPIO pin number of %d\n",pin);
        return -1;
    }

    if(value < 0 || value > 1)
    {
        fprintf(stderr, "Invalid value of %d\n",value);
        return -1;
    }
   
    f = fopen(pinpath,"w");
    fprintf(f,"%d",value);
    fclose(f);
    return 0;
}

/** 
 * gpio_rpi3_read - read input of GPIO pin
 * @pin: GPIO pin
 *
 * returns -1 if invalid input
 * returns input that was read ( 0 or 1)
 **/
int gpio_rpi3_read(int pin)
{
    FILE *f;
    char pinpath[40];
    int x;
    sprintf(pinpath,"%s%d/value",PATH,pin); // concatenate for GPIO# director path

    // Test for invalid inputs
    if(pin < 2 || pin > 27)
    {
        fprintf(stderr,"Invalid GPIO pin number of %d\n",pin);
        return -1;
    }
    
    // read value of input
    f = fopen(pinpath,"r");
    if((x = fgetc(f))!=EOF)
        x = (x==49); // 49 == ASCII symbol 1
    else
        x = -1;
    
    fclose(f);
    return x;
}
