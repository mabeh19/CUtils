CC=gcc
SOURCES=test_bench_test.c ./Test_Bench/Test_Bench.c ../datatypes/string/cstring.c ../collections/iterator/Iterator.c
TARGET=test_bench_test
FLAGS=-Wall -fsanitize=address


phony: all

all:
	$(CC) $(FLAGS) $(SOURCES) -o $(TARGET)
	$(CC) test_utest.c uTest/uTest.c ../collections/linked_list/LinkedList.c -o test_utest
