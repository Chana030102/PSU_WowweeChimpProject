/*
   RPi3_MCP3008.h (C) Aaron Chan
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
 * Library developed for Raspberry Pi 3
 * Tested on Raspberry Pi 3 Model B Vi 2
 */
#include <stdio.h>
#include "gpio_rpi3.h"

#define SPI_CLOCK 11
#define SPI_MOSI  10
#define SPI_MISO   9
#define SPI_CE0_N  8

/*============ PROTOTYPES ============*/
void clocked_write(int clockpin, int out, int value);
int clocked_read(int clockpin, int in);
int power_of_2();

void mcp3008_setconfig_bits(int config_bits[], int mode, int channel);
int mcp3008_get_val(int channel, int clockpin, int in, int out, int cs);

/**
 * clocked_write - synchronous write to device
 * @clockpin - GPIO pin that will act as clock
 * @out - output GPIO pin
 **/
void clocked_write(int clockpin, int out, int value)
{
    gpio_rpi3_write(out, value);
    gpio_rpi3_write(clockpin,1);
    gpio_rpi3_write(clockpin,0);
}

/**
 * clocked_read - synchronous digital read from device
 * @clockpin - GPIO pin that will act as clock
 * @in - input GPIO pin
 *
 * returns value read from input (1 or 0)
 **/
int clocked_read(int clockpin, int in)
{
   gpio_rpi3_write(clockpin,1); 
   gpio_rpi3_write(clockpin,0);
   return gpio_rpi3_read(in);
}

/**
 * mcp3008_setconfig_bits - write config bits to MCP3008
 *
 * The following info is from the datasheet:
 * Configuration Bits in total are 5:
 * [start, SGL/DIFF, D2, D1, D0]
 *  + start --> is a HIGH
 *  + SGL/DFF --> HIGH for single-ended
 *                LOW for differential
 *  + D[2:0] --> 3 bit number for desired analog channel
 *
 **/
void mcp3008_setconfig_bits(int config_bits[], int mode, int channel)
{
   int i;
   
   config_bits[0] = 1; // start bit
   config_bits[1] = mode; // SGL/DFF bit
   
   // Convert channel into bit representation and store.
   for(i=0;i<3;i++)
       config_bits[i+2] = (channel >> (2-i)) & 1;
}


/**
 * mcp3007_get_val - convert input value from ADC channel
 * 
 * Using SPI communication method, we read 3 bytes from
 * MCP3008 starting from MSB. Note that bits 8 and 9 do not mean anything.
 * return -1 if invalid inputs
 * returns converted value (ranging from 0 - 1023)
 **/
int mcp3008_get_val(int channel, int clockpin, int in, int out, int cs)
{
    int i;
    int output = 0; // return read value
    int config_bits[5]; // MCP3008 config bits

    // Test for invalid inputs
    if(channel < 0 || channel > 7)
    {
        fprintf(stderr,"Channel %d is does not exist\n",channel);
        return -1;
    }
    
    // Setup and initialize
    gpio_rpi3_set(clockpin, "in");
    gpio_rpi3_set(in,"in");
    gpio_rpi3_set(out,"out");
    gpio_rpi3_set(cs,"out");
   
    mcp3008_setconfig_bits(config_bits,1,channel); // Get config bits

    // Initiate SPI communication
    gpio_rpi3_write(cs, 1);
    gpio_rpi3_write(clockpin,0);
    gpio_rpi3_write(cs,0);

    // Configure MCP3008 to single-ended 
    for(i=0;i<5;i++)
    {   clocked_write(clockpin,out,config_bits[i]); }

    // Read 3 bytes, but bits 8 and 9 don't mean anything.
    for(i=12; i>0; i--)
    {
        if(clocked_read(clockpin,in) && i<11)
        { output += (1 << i); }
    }

    // End SPI communication
    gpio_rpi3_write(cs, 1);
    return output;
}
