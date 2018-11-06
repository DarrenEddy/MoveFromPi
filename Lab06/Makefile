CC=gcc
CFLAGS=-lWarn -pedantic

thermo: thermo.o libmyifttt.a
	cc thermo.o -L. -lmyifttt -lcurl -lwiringPi -o thermo

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<
