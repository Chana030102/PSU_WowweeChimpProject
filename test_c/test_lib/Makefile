#Makefile for test programs for RPi3 GPIO library

all: blink testconfig 

blink: blink_LED.c
	gcc -g -Wall -o blink_LED blink_LED.c

adc: read_adc.c
	gcc -g -Wall -o read_adc read_adc.c

clean:
	rm -f blink_LED read_adc
