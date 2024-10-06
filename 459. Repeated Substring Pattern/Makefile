CC=gcc
CFLAGS=-Wall -Wextra -O2 -std=c99
TARGET=repeated_substring_pattern

.PHONY: all clean test

all: test

test: $(TARGET)
	@echo "Running unit tests..."
	@./$<

$(TARGET): repeated_substring_pattern.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)

