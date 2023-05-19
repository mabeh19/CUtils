#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hashmap.h"
#include "../key_vec/keyvec.h"

#define AS_MAP(m)       ((HashMap_t *)m)
#define NEW_TABLE_SIZE  ((uint32_t)10)

typedef struct {  
        KeyVector **table;
        size_t len;
        size_t keysize;
        size_t valsize;
} HashMap_t;

static size_t __hashingFunction__(HashMap_t *map, void *key);

static size_t __hashingFunction__(HashMap_t *map, void *key)
{
        uint8_t *b = key;
        size_t hash = 0;

        for (uint8_t i = 0; i < map->keysize; i++)
        {
                hash += *b;
                hash *= *b;
        }

        return hash % map->len;
}

HashMap *HashMap_new(size_t keySize, size_t valueSize)
{
        HashMap_t *__map__ = (HashMap_t *)malloc(sizeof(HashMap_t));
        __map__->table = (KeyVector **)malloc(NEW_TABLE_SIZE * sizeof(KeyVector *));

        // Init table
        for (size_t i = 0; i < NEW_TABLE_SIZE; i++)
                __map__->table[i] = KeyVector_new(valueSize, keySize);

        __map__->len = NEW_TABLE_SIZE;
        __map__->keysize = keySize;
        __map__->valsize = valueSize;

        return (HashMap *)__map__;
}

void HashMap_delete(HashMap *map)
{
        HashMap_t *m = AS_MAP(map);

        // Call deconstructors for each bucket
        for (size_t i = 0; i < m->len; i++)
                KeyVector_delete(m->table[i]);

        // Free table
        free(m->table);

        // Finally free pointer
        free(m);
}

void *HashMap_get(HashMap *map, void *key)
{
        HashMap_t *m = AS_MAP(map);
        size_t index = __hashingFunction__(m, key);
        KeyVector *bucket = m->table[index];

        void *val = KeyVector_get(bucket, key);

        return val;
}

bool HashMap_insert(HashMap *map, void *key, void *value)
{
        HashMap_t *m = AS_MAP(map);
        size_t index = __hashingFunction__(m, key);

        KeyVector *bucket = m->table[index];
        KeyVector_push_back(bucket, key, value);

        return true;
}

void HashMap_print(HashMap *map, KeyVectorCallback printMethod)
{
        HashMap_t *m = AS_MAP(map);

        printf("== TABLE BEGIN ==\n");
        for (size_t i = 0; i < m->len; i++)
                KeyVector_print(m->table[i], printMethod);

        printf("== TABLE  END ==\n");
}

static void HashMap_reinitTable(HashMap *map, KeyVector **newTable)
{
        HashMap_t* _map = (HashMap_t*)map;
        for (uint32_t i = 0; i < _map->len; i++)
        {
                KeyVector *vec = _map->table[i];
                ssize_t vecLen = KeyVector_len(vec);
                for (uint32_t j = 0; j < vecLen; j++)
                {
                        void *k, *v;
                        KeyVector_getKeyValPair(vec, j, &k, &v);

                        uint32_t index = __hashingFunction__(_map, k);
                }
        }
}

static void HashMap_expandTable(HashMap_t *map)
{
        KeyVector **newTable = realloc(map->table, (map->len + NEW_TABLE_SIZE) * sizeof(KeyVector **));
        
}

static void HashMap_shrinkTable(HashMap_t *map)
{
        map->table = realloc(map->table, (map->len - NEW_TABLE_SIZE) * sizeof(KeyVector **));
}
