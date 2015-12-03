cflags= -Wall -Wextra -std=c99

all: build test

tests:
	cd tests && $(MAKE)

slice: slice.c 
	gcc $(cflags) slice.o -o slice

build: sl.o test.o sl.h
	gcc test.o sl.o -o test

run: build
	./test

list.o : sl.c sl.h
	gcc -c list.c

test.o : test.c sl.h
	gcc -c test.c

clean:
	rm *.o test
