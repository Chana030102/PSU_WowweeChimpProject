#

all: test test2

test: test.c
	gcc -g -Wall -o test test.c -lwiringPi

test2: test2.c
	gcc -g -Wall -o test2 test2.c -lwiringPi

clean:
	rm -f test test2
