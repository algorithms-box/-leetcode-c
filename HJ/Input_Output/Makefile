CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g
TARGET=main
SOURCES=$(TARGET).c
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./${TARGET}

clean:
	rm -rf $(TARGET) $(OBJECTS)
