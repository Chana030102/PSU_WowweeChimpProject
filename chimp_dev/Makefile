#

all: test test2 test3 turn_off

test: test.c
	gcc -g -Wall -o test test.c -lwiringPi

test2: test2.c
	gcc -g -Wall -o test2 test2.c -lwiringPi

test3: test3.c
	gcc -g -Wall -o test3 test3.c -lwiringPi

turn_off: turn_off.c
	gcc -g -Wall -o turn_off.c -lwiringPi

clean:
	rm -f test test2 test3 turn_off
