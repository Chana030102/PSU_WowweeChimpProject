#test programs using wiringPi

all: blink adc


blink: blink_LED.c
	gcc -g -Wall -o blink blink_LED.c -lwiringPi

adc: read_adc.c
	gcc -g -Wall -o adc read_adc.c -lwiringPi

clean: 
	rm -f blink adc
