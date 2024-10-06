# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -O3

all: longest_common_prefix

longest_common_prefix: longest_common_prefix.c
	$(CC) $(CFLAGS) -o $@ $<

test: longest_common_prefix
	./longest_common_prefix

clean:
	rm longest_common_prefix

