cflags= -g -Wall -Wextra -std=c99
prefix=/usr/local

.PHONY: all test run clean install

all: test 

test:
	cd tests && $(MAKE)

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


