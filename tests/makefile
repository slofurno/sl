cflags= -Wall -Wextra -std=c99

.PHONY: all test clean

all: test

slice: slice.c
	gcc $(cflags) slice.c -o slice

skiplist: skiplist.c input.c
	gcc $(cflags) skiplist.c -o skiplist

input.c: makestrings.sh
	sh ./makestrings.sh

test: slice skiplist
	./slice
	./skiplist

clean:
	rm input.c
