CC = clang
RELEASE_TARGET = sort
TEST_TARGET = test_sort
SOURCES = $(wildcard *.c) $(wildcard */*.c)
RELEASE_FLAGS = -DRELEASE
TEST_FLAGS = -DTEST -lcmocka


phony: release

release:
	$(CC) $(SOURCES) $(RELEASE_FLAGS) -o $(RELEASE_TARGET)

test:
	$(CC) $(SOURCES) $(TEST_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)
	rm ./$(TEST_TARGET)
