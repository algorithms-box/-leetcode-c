CC=gcc
CFLAGS=-pthread -Wall

all: main

main: main.o dining_philosophers.o
	$(CC) $(CFLAGS) -o main main.o dining_philosophers.o

main.o: main.c dining_philosophers.h
	$(CC) $(CFLAGS) -c main.c

dining_philosophers.o: dining_philosophers.c dining_philosophers.h
	$(CC) $(CFLAGS) -c dining_philosophers.c

clean:
	rm -f *.o main