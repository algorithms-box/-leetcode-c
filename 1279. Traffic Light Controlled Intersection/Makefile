CC=gcc
CFLAGS=-Wall -Wextra -pthread
TARGET=test_traffic_light

all: $(TARGET)

$(TARGET): test_traffic_light.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)