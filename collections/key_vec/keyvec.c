#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "keyvec.h"

typedef struct __keyvec_element__ {
        void *key;
        void *data;
        struct __keyvec_element__ *next;
        struct __keyvec_element__ *prev;
} __KeyVectorElement_t__;

typedef struct __keyvector__ {
        __KeyVectorElement_t__ *__first__;
        __KeyVectorElement_t__ *__last__;
        size_t __len__;
        size_t __key_size__;
        size_t __data_size__;
} KeyVector_t;

#define AS_INTERNAL()     KeyVector_t* vec = (KeyVector_t*)vector

static __KeyVectorElement_t__ *__alloc__elem(KeyVector_t* vector, void *key, void *data);

KeyVector *KeyVector_new(size_t dataSize, size_t keySize)
{
        KeyVector_t *new_vec = (KeyVector_t *)malloc(sizeof(KeyVector_t));
        
        new_vec->__first__ = NULL;
        new_vec->__last__  = NULL;
        new_vec->__len__ = 0;
        new_vec->__data_size__ = dataSize;
        new_vec->__key_size__ = keySize;
        return (KeyVector*)new_vec;
}

void KeyVector_delete(KeyVector *vector)
{
        if (!vector) return;
        AS_INTERNAL();
        __KeyVectorElement_t__ *__elem__ = vec->__last__;
        while (vec->__len__-- > 0)
        {
                free(__elem__->data);
                free(__elem__->key);
                if (!__elem__->prev)
                        break;

                __elem__ = __elem__->prev;
                free(__elem__->next);
        }

        free(__elem__);
        free(vector);
}

void *KeyVector_get(KeyVector *vector, void *key)
{
        if (!vector) return NULL;
        AS_INTERNAL();
        if ( key == NULL ) return NULL;
        __KeyVectorElement_t__ *__elem__ = vec->__first__;

        for (uint32_t i = 0; i < vec->__len__; i++)
                if (memcmp(key, __elem__->key, vec->__key_size__) == 0)
                        break;
                else
                        __elem__ = __elem__->next;

        return __elem__->data;
}

void *KeyVector_first(KeyVector *vector)
{
        if (!vector) return NULL;
        AS_INTERNAL();
        return vec->__first__;
}

void *KeyVector_last(KeyVector *vector)
{
        if (!vector) return NULL;
        AS_INTERNAL();
        return vec->__last__;
}

ssize_t KeyVector_len(KeyVector *vector)
{
        if (!vector) return -1;
        AS_INTERNAL();
        return vec->__len__;
}

void KeyVector_push_back(KeyVector *vector, void *key, void *data)
{
        if (!vector || !data) return;
        AS_INTERNAL();
        __KeyVectorElement_t__ *__new_elem__ = __alloc__elem(vec, key, data);
        __new_elem__->next = NULL;
        __new_elem__->prev = vec->__last__;
        if (!vec->__first__)
                vec->__first__ = __new_elem__;
        else
                vec->__last__->next = __new_elem__;
        vec->__last__ = __new_elem__;
        vec->__len__++;
}

void KeyVector_push_front(KeyVector *vector, void *key, void *data)
{
        if (!vector || !data) return;
        AS_INTERNAL();
        __KeyVectorElement_t__ *__new_elem__ =	__alloc__elem(vec, key, data);
        __new_elem__->next = vec->__first__;
        __new_elem__->prev = NULL;
        if (!vec->__first__)
                vec->__first__ = __new_elem__;
        else
                vec->__first__->prev = __new_elem__;
        vec->__first__ = __new_elem__;
        vec->__len__++;
}

void *KeyVector_pop_back(KeyVector *vector)
{
        if (!vector) return NULL;
        AS_INTERNAL();
        void *ret = vec->__last__->data;
        __KeyVectorElement_t__ *tmp = vec->__last__;
        vec->__last__ = vec->__last__->prev;
        vec->__len__--;
        free(tmp);
        return ret;
}

void *KeyVector_pop_front(KeyVector *vector)
{
        if (!vector) return NULL;
        AS_INTERNAL();
        void *ret = vec->__first__->data;
        __KeyVectorElement_t__ *tmp = vec->__first__;
        vec->__first__ = vec->__first__->next;
        vec->__len__--;
        free(tmp);
        return ret;
}

void KeyVector_foreach(KeyVector *vector, KeyVectorCallback callback)
{
        if (!vector || !callback) return;
        AS_INTERNAL();
        for (__KeyVectorElement_t__ *elem = vec->__first__; elem != NULL; elem = elem->next)
        {
                callback(elem->data);
        }
}

void KeyVector_getKeyValPair(KeyVector *vector, uint32_t index, void **key, void **data)
{
AS_INTERNAL();
        uint32_t i = 0;
        __KeyVectorElement_t__ *elem;
        for (elem = vec->__first__; i++ < index; elem = elem->next);

        *key = elem->key;
        *data = elem->data;
}

static __KeyVectorElement_t__ *__alloc__elem(KeyVector_t *vector, void *key, void *data)
{
        __KeyVectorElement_t__ *__new_elem__ = (__KeyVectorElement_t__ *)malloc(sizeof(__KeyVectorElement_t__));
        __new_elem__->key = malloc(vector->__key_size__);
        __new_elem__->data = malloc(vector->__data_size__);
        memcpy(__new_elem__->key, key, vector->__key_size__);
        memcpy(__new_elem__->data, data, vector->__data_size__);
        return __new_elem__;
}

void KeyVector_print(KeyVector *vector, KeyVectorCallback printMethod)
{
AS_INTERNAL();
        __KeyVectorElement_t__ *__elem__ = vec->__first__;
        printf("[ ");
        if ( vec->__len__ == 0)
                printf("--EMPTY--");
        else
        {
                for (uint32_t i = 0; i < (vec->__len__ - 1); i++)
                {
                        printMethod(__elem__->data);
                        printf(" -- ");
                        __elem__ = __elem__->next;
                }
                printMethod(vec->__last__->data);
        }
        printf(" ]\n");
}


Iterator* KeyVector_ToIter(KeyVector *vector)
{

}
