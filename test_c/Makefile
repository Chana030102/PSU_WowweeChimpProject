#Makefile for test programs for RPi3 GPIO library

all: blink testconfig 

blink: blink_LED.c
	gcc -g -Wall -o blink_LED blink_LED.c

config_bit: config_bit.c
	gcc -g -Wall -o config_bit config_bit.c

clean:
	rm -f blink_LED config_bit
