CC=gcc
SOURCES=test_bench_test.c 
TARGET=test_bench_test
FLAGS=-Wall -fsanitize=address -g3


phony: all

all:
	$(CC) $(FLAGS) $(SOURCES) -o $(TARGET)
	$(CC) $(FLAGS) test_utest.c test_utest2.c -o test_utest
