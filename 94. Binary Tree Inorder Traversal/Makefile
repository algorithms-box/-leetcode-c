CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2
TARGET=inorder_traversal

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $@ $<

run:
	./$(TARGET)


clean:
	rm -rf $(TARGET)

