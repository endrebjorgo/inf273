CC = clang
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = bin/main
SRC = src/main.c 

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

