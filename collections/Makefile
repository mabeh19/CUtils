SOURCES=$(wildcard *.c) $(wildcard */*.c)
FLAGS=-o test -fsanitize=address
phony: all

all:
	gcc ${SOURCES} ${FLAGS}
