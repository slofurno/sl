
all: run


build:
	gcc sl.c -o sl.exe

run: build 
	./sl.exe
