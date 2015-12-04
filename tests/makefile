cflags= -Wall -Wextra -std=c99

.PHONY: all test 

all: test

slice: slice.c
	gcc $(cflags) slice.c -o slice

skiplist: skiplist.c
	gcc $(cflags) skiplist.c -o skiplist

test: slice skiplist
	./slice > slice.log
	./skiplist > skiplist.log
