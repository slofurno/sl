cflags= -Wall -Wextra -std=c99
prefix=/usr/local


all: build test build_shared install

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
	rm *.o *.so test

libslice.so: slice.c slice.h
	gcc $(cflags) -shared -o libslice.so -fPIC slice.c

install: libslice.so
	install -m 0755 libslice.so $(prefix)/lib
	install -d $(prefix)/include/sl
	install -m 0644 -D *.h $(prefix)/include/sl
