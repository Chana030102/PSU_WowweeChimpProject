#

all: test test2 test3 test4 off

test: test.c
	gcc -g -Wall -o test test.c -lwiringPi

test2: test2.c
	gcc -g -Wall -o test2 test2.c -lwiringPi

test3: test3.c
	gcc -g -Wall -o test3 test3.c -lwiringPi

test4: test4.c
	gcc -g -Wall -o test4 test4.c -lwiringPi

off: off.c
	gcc -g -Wall -o off.c -lwiringPi

clean:
	rm -f test test2 test3 test4 off
