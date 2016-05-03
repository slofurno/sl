cflags= -g -Wall -Wextra -std=c99
prefix=/usr/local

.PHONY: all test run clean install

all: test

test:
	cd tests && $(MAKE)

clean:
	rm -f *.o *.so *.a

libslice.so: slice.c slice.h
	gcc $(cflags) -shared -o libslice.so -fPIC slice.c

install: libslice.so libskiplist.so libskiplist.a
	install -m 0755 libslice.so $(prefix)/lib
	install -m 0755 libskiplist.so $(prefix)/lib
	install -m 0755 libskiplist.a $(prefix)/lib
	install -d $(prefix)/include/sl
	install -m 0644 -D *.h $(prefix)/include/sl

libskiplist.a: skiplist.c skiplist.h
	gcc $(cflags) -c skiplist.c -o skiplist.o
	ar -cvq libskiplist.a skiplist.o
	rm skiplist.o

libskiplist.so: skiplist.c skiplist.h
	gcc $(cflags) -shared -o libskiplist.so -fPIC skiplist.c

