cflags= -Wall -Wextra -std=c99
prefix=/usr/local

.PHONY: all tests run clean install

all: build test 

tests:
	cd tests && $(MAKE)

slice: slice.c 
	gcc $(cflags) slice.o -o slice

build: skiplist.o test.o skiplist.h
	gcc test.o skiplist.o -o test

run: build
	./test

list.o : skiplist.c skiplist.h
	gcc -c list.c

test.o : test.c skiplist.h
	gcc -c test.c

clean:
	rm *.o *.so test

libslice.so: slice.c slice.h
	gcc $(cflags) -shared -o libslice.so -fPIC slice.c

install: libslice.so libskiplist.so
	install -m 0755 libslice.so $(prefix)/lib
	install -m 0755 libskiplist.so $(prefix)/lib
	install -d $(prefix)/include/sl
	install -m 0644 -D *.h $(prefix)/include/sl

libskiplist.so: skiplist.c skiplist.h
	gcc $(cflags) -shared -o libskiplist.so -fPIC skiplist.c


