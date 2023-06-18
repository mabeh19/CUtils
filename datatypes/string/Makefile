FLAGS=--std=c17 -O3

phony: all


all:
	gcc $(FLAGS) -c cstring.c -o cstring.o
	ar rcs libcstring.a cstring.o

test:
	gcc $(FLAGS) *.c -o test
