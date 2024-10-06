CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = maximum_repeating_substring

$(TARGET): maximum_repeating_substring.c
	$(CC) $(CFLAGS) -o $(TARGET) maximum_repeating_substring.c

.PHONY: clean test

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
