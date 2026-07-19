CC = gcc

CFLAGS = -Wall -Wextra -pedantic -Iinclude

SRC := $(shell find src -name "*.c")
OBJ := $(patsubst src/%.c,build/%.o,$(SRC))

TARGET = build/program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
