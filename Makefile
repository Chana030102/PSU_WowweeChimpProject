# 

all: testA

testA: motor.c
	gcc -g -Wall -o testA motor.c -lwiringPi


clean:
	rm -f testA
