CC = clang
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = bin/main
SRC = $(wildcard src/*.c)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

