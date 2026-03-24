CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
SRC = src/allocator.c
DEMO_SRC = examples/demo.c
TEST_SRC = tests/test_allocator.c

all: demo test

demo:
	mkdir -p bin
	$(CC) $(CFLAGS) $(DEMO_SRC) $(SRC) -o bin/demo

test:
	mkdir -p bin
	$(CC) $(CFLAGS) -c $(SRC) -o bin/allocator.o
	$(CC) $(CFLAGS) -c $(TEST_SRC) -o bin/test_allocator.o
	$(CC) bin/test_allocator.o bin/allocator.o -o bin/test_allocator

clean:
	rm -rf bin