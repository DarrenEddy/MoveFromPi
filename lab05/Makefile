CC=gcc
CFLAGS=-lWarn -pedantic

alarm: alarm.o libmyifttt.a
	cc alarm.o -L. -lmyifttt -lcurl -lwiringPi -o alarm

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<
