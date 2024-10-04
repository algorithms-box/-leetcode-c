CC = gcc
CFLAGS = -pthread -Wall -std=c11

all: traffic_light

traffic_light: traffic_light.c
	$(CC) $(CFLAGS) -o traffic_light traffic_light.c

test:
	./traffic_light test

clean:
	rm -f traffic_light