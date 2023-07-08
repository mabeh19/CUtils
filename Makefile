CC = gcc
FLAGS = --std=c11 -W -fsanitize=address
LIB_FLAGS = --std=c17 -O3 -c
SOURCES = *.c */*.c */*/*.c
TARGET = test_utils

COLLECTION_SOURCES = ./collections/*/*.c
LIB_COLLECTION = $(COLLECTION_SOURCES:.c=.o)

DATATYPES_SOURCES = ./datatypes/*/*.c
LIB_DATATYPES = $(DATATYPES_SOURCES:.c=.o)

all:
	$(CC) $(LIB_FLAGS) $(COLLECTION_SOURCES) #-o $(LIB_COLLECTION)
	$(CC) $(LIB_FLAGS) $(DATATYPES_SOURCES) #-o $(LIB_DATATYPES)
	ar rcs libcutils *.o

clean:
	rm -r *.o *.a
