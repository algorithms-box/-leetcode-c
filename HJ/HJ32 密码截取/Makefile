CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test

