CC = gcc
FLAGS = --std=c11 -W -fsanitize=address
LIB_FLAGS = --std=c17 -O3 -c
SOURCES = *.c */*.c
TARGET = test_utils
VECTOR_SOURCES = ./vector/vector.c
LIB_VECTOR = vector.o
KEYVEC_SOURCES = ./key_vec/keyvec.c
LIB_KEYVEC = keyvector.o
HASHMAP_SOURCES = ./hashmap/hashmap.c -lkeyvector
LIB_MAP = hashmap.o

all:
	#$(CC) $(FLAGS) $(SOURCES) -o $(TARGET)
	$(CC) $(LIB_FLAGS) $(VECTOR_SOURCES) -o $(LIB_VECTOR)
	ar rcs libvector.a $(LIB_VECTOR)
	$(CC) $(LIB_FLAGS) $(KEYVEC_SOURCES) -o $(LIB_KEYVEC)
	ar rcs libkeyvector.a $(LIB_KEYVEC)
	$(CC) $(LIB_FLAGS) $(HASHMAP_SOURCES) -o $(LIB_MAP)
	ar rcs libhashmap.a $(LIB_MAP)
