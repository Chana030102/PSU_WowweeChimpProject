# Makefile for test programs for RPi3 GPIO library

all: blink testconfig 

blink: blink_LED.c
	gcc -g -o blink_LED blink_LED.c

testconfig: config_bit.c
	gcc -g -o testconfig config_bit.c
