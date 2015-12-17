cflags= -g -Wall -Wextra -std=c99
prefix=/usr/local

.PHONY: all tests run clean install

all: tests 

tests:
	cd tests && $(MAKE)

test: test_skiplist 
	./test_skiplist > test.out

slice: slice.c 
	gcc $(cflags) slice.o -o slice

test_skiplist: skiplist.o test_skiplist.o
	gcc test_skiplist.o skiplist.o -o test_skiplist

list.o : skiplist.c skiplist.h
	gcc -c list.c

test_skiplist.o : test_skiplist.c skiplist.h
	gcc -c test_skiplist.c

clean:
	rm -f *.o *.so

libslice.so: slice.c slice.h
	gcc $(cflags) -shared -o libslice.so -fPIC slice.c

install: libslice.so libskiplist.so
	install -m 0755 libslice.so $(prefix)/lib
	install -m 0755 libskiplist.so $(prefix)/lib
	install -d $(prefix)/include/sl
	install -m 0644 -D *.h $(prefix)/include/sl

libskiplist.so: skiplist.c skiplist.h
	gcc $(cflags) -shared -o libskiplist.so -fPIC skiplist.c


