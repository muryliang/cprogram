CFLAGS = -Wall -g
cc = gcc

all: ex19

ex19 : object.o

ex19.pp : object.c object.h ex19.c ex19.h
	gcc -E object.c ex19.c 

clean:
	rm -rf ex19 ex19.o object.o
