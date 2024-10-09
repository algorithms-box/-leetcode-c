CC=gcc
CFLAGS=-std=c99 -Wall

all: main

main: main.o
	$(CC) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

test:
	./main

clean:
	rm -f *.o main
