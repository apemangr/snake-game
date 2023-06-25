CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lraylib -lm

TARGET = snake 
SOURCES = main.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET)
