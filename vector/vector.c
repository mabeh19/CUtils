#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "vector.h"

typedef struct __element__ {
        void *data;
        struct __element__ *next;
        struct __element__ *prev;
} __VectorElement_t__;

typedef struct __vector__ {
        __VectorElement_t__ *__first__;
        __VectorElement_t__ *__last__;
        size_t __len__;
        size_t __data_size__;
} Vector_t;



static __VectorElement_t__ *__alloc__elem(Vector_t *vector, void *data);

Vector *Vector_new(size_t dataSize)
{
        Vector_t *new_vec = (Vector_t *)malloc(sizeof(Vector));

        new_vec->__first__ = NULL;
        new_vec->__last__  = NULL;
        new_vec->__len__ = 0;
        new_vec->__data_size__ = dataSize;
        return (Vector *)new_vec;
}

void Vector_delete(Vector *vector)
{
        if (!vector) return;
        Vector_t *vec = (Vector_t *)vector;
        __VectorElement_t__ *__elem__ = vec->__last__;
        while (vec->__len__ > 0) {
                free(__elem__->data);

                if (!__elem__->prev)
                        break;

                __elem__ = __elem__->prev;
                free(__elem__->next);
        }

        free(__elem__);
        free(vector);
}

void *Vector_get(Vector *vector, size_t n)
{
        if (!vector) return NULL;
        Vector_t *vec = (Vector_t *)vector;
        if (n >= vec->__len__) return NULL;
        __VectorElement_t__ *__elem__;
        if (n >= (vec->__len__ * 0.5))
                {
                        __elem__ = vec->__last__;
                        for (uint32_t i = vec->__len__ - 1; i > n; i--)
                                __elem__ = __elem__->prev;
                }
                else
                {
                __elem__ = vec->__first__;
                for (uint32_t i = 0; i < n; i++)
                        __elem__ = __elem__->next;
        }

        return __elem__->data;
}

void *Vector_first(Vector *vector)
{
        if (!vector) return NULL;
        Vector_t *vec = (Vector_t *)vector;
        return vec->__first__;
}

void *Vector_last(Vector *vector)
{
        if (!vector) return NULL;
        Vector_t *vec = (Vector_t *)vector;
        return vec->__last__;
}

ssize_t Vector_len(Vector *vector)
{
        if (!vector) return -1;
        Vector_t *vec = (Vector_t *)vector;
        return vec->__len__;
}

void Vector_push_back(Vector *vector, void *data)
{
        if (!vector || !data) return;
        Vector_t *vec = (Vector_t *)vector;
        __VectorElement_t__ *__new_elem__ = __alloc__elem(vec, data);
        __new_elem__->next = NULL;
        __new_elem__->prev = vec->__last__;
        if (!vec->__first__)
                vec->__first__ = __new_elem__;
else
vec->__last__->next = __new_elem__;
vec->__last__ = __new_elem__;
vec->__len__++;
}

void Vector_push_front(Vector *vector, void *data)
{
        if (!vector || !data) return;
        Vector_t *vec = (Vector_t *)vector;
        __VectorElement_t__ *__new_elem__ =	__alloc__elem(vec, data);
        __new_elem__->next = vec->__first__;
        __new_elem__->prev = NULL;
        if (!vec->__first__)
                vec->__first__ = __new_elem__;
                else
                vec->__first__->prev = __new_elem__;
        vec->__first__ = __new_elem__;
        vec->__len__++;
}

void *Vector_pop_back(Vector *vector)
{
        if (!vector) return NULL;
        Vector_t *vec = (Vector_t *)vector;
        void *ret = vec->__last__->data;
        __VectorElement_t__ *tmp = vec->__last__;
        vec->__last__ = vec->__last__->prev;
        vec->__len__--;
        free(tmp);
        return ret;
}

void *Vector_pop_front(Vector *vector)
{
        if (!vector) return NULL;
        Vector_t *vec = (Vector_t *)vector;
        void *ret = vec->__first__->data;
        __VectorElement_t__ *tmp = vec->__first__;
        vec->__first__ = vec->__first__->next;
        vec->__len__--;
        free(tmp);
        return ret;
}

void Vector_foreach(Vector *vector, VectorCallback callback)
{
        if (!vector || !callback) return;
        Vector_t *vec = (Vector_t *)vector;
        for (__VectorElement_t__ *elem = vec->__first__; elem != NULL; elem = elem->next)
        {
                callback(elem->data);
        }
}

static __VectorElement_t__ *__alloc__elem(Vector_t *vector, void *data)
{
        __VectorElement_t__ *__new_elem__ = (__VectorElement_t__ *)malloc(sizeof(__VectorElement_t__));
        __new_elem__->data = malloc(vector->__data_size__);
        memcpy(__new_elem__->data, data, vector->__data_size__);
        return __new_elem__;
}

void Vector_print(Vector *vector, VectorCallback printMethod)
{
        Vector_t *vec = (Vector_t *)vector;
        __VectorElement_t__ *__elem__ = vec->__first__;
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
