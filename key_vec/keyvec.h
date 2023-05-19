

#ifndef __KEYVEC_H__
#define __KEYVEC_H__

#include <sys/types.h>
#include <stdint.h>

typedef struct {} KeyVector;

typedef void (*KeyVectorCallback)(void *vectorElem);

KeyVector *KeyVector_new(size_t dataSize, size_t keySize);
void KeyVector_delete(KeyVector *vector);
void *KeyVector_get(KeyVector *vector, void *key);
void *KeyVector_first(KeyVector *vector);
void *KeyVector_last(KeyVector *vector);
ssize_t KeyVector_len(KeyVector *vector);
void KeyVector_push_back(KeyVector *vector, void *key, void *data);
void KeyVector_push_front(KeyVector *vector, void *key, void *data);
void *KeyVector_pop_back(KeyVector *vector);
void *KeyVector_pop_front(KeyVector *vector);
void KeyVector_foreach(KeyVector *vector, KeyVectorCallback callback);
void KeyVector_print(KeyVector *vector, KeyVectorCallback printMethod);
void KeyVector_getKeyValPair(KeyVector *vector, uint32_t index, void **key, void **data);

#endif
