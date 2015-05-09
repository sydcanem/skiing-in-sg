CC = cc
CFLAGS = -std=c99 -pedantic -g -Wall

all: main

main: main.o skigrid.o
	$(CC) $(CFLAGS) -o main.exe main.o skigrid.o

skigrid.o: skigrid.c skigrid.h
	$(CC) $(CFLAGS) -c skigrid.c

clean:
	$(RM) main.exe *.o *~