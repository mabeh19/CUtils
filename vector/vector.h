

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <sys/types.h>

typedef struct {} Vector;

typedef void (*VectorCallback)(void *vectorElem);

Vector *Vector_new(size_t dataSize);
void Vector_delete(Vector *vector);
void *Vector_get(Vector *vector, size_t n);
void *Vector_first(Vector *vector);
void *Vector_last(Vector *vector);
ssize_t Vector_len(Vector *vector);
void Vector_push_back(Vector *vector, void *data);
void Vector_push_front(Vector *vector, void *data);
void *Vector_pop_back(Vector *vector);
void *Vector_pop_front(Vector *vector); 
void Vector_foreach(Vector *vector, VectorCallback callback);
void Vector_print(Vector *vector, VectorCallback printMethod);

#endif
