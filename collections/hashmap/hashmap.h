

#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <sys/types.h>
#include <stdbool.h>

#include "../key_vec/keyvec.h"

typedef struct HashMap HashMap;

HashMap *HashMap_new(size_t keySize, size_t valueSize);
void HashMap_delete(HashMap *map);
bool HashMap_insert(HashMap *map, void *key, void *value);
void *HashMap_get(HashMap *map, void *key);
void HashMap_print(HashMap *map, KeyVectorCallback printMethod);

Iterator* HashMap_ToIter(HashMap *map);

#endif

