cflags= -Wall -Wextra -std=c99

.PHONY: all

all: test

slice_test: slice_test.c
	gcc $(cflags) slice_test.c -o slice_test

test: slice_test
	./slice_test
