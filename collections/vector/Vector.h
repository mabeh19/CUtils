

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdlib.h>
#include <string.h>
#include "../Results.h"
#include "../iterator/Iterator.h"

typedef struct{} Vector;

#define ARRAY_STEP_SIZE     5
#define AS_VEC(type)       Vector##type##_t* v = (Vector##type##_t*)vector;


#define Vector_New(type)        Vector##type##_New()
#define Vector_Delete(type, vector)     Vector##type##_Delete(vector)
#define Vector_Len(type, vector)     Vector##type##_Len(vector)
#define Vector_Push(type, vector, val)     Vector##type##_Push(vector, val)
#define Vector_Pop(type, vector)     Vector##type##_Pop(vector)
#define Vector_Get(type, vector, idx)     Vector##type##_Get(vector, idx)
#define Vector_ToIter(type, vector)     Vector##type##_ToIter(vector)

#define DECLARE_VECTOR_TYPE(type)                                                       \
        Vector* Vector##type##_New(void);                                                 \
        void Vector##type##_Delete(Vector* vector);                                       \
        RESULT(size_t) Vector##type##_Len(const Vector* vector);                          \
        RESULT(size_t) Vector##type##_Push(Vector* vector, type val);                     \
        RESULT(type) Vector##type##_Pop(Vector* vector);                                  \
        RESULT(type) Vector##type##_Get(const Vector* vector, size_t index);              \
        Iterator* Vector##type##_ToIter(const Vector* vector);                          


#define DEFINE_VECTOR_TYPE(type)                                                \
typedef struct {                                                \
    size_t len;                                         \
    size_t total_size;                                          \
    type* array;                                         \
} Vector##type##_t;                                             \
                                                \
                                                \
Vector* Vector##type##_New(void)                                                \
{                                               \
    Vector##type##_t* v = malloc(sizeof(Vector##type##_t));                                             \
                                                \
    v->len = 0;                                         \
    v->array = malloc(ARRAY_STEP_SIZE * sizeof(type));                                           \
    v->total_size = ARRAY_STEP_SIZE;                                            \
                                                \
    return (Vector*)v;                                          \
}                                               \
                                                \
void Vector##type##_Delete(Vector *vector)                                              \
{                                               \
    if (!vector)                                                \
        return;                                         \
                                                \
    AS_VEC(type);                                              \
                                                \
    free(v->array);                                             \
    free(v);                                            \
}                                               \
                                                \
RESULT(size_t) Vector##type##_Len(const Vector* vector)                                         \
{                                               \
    if (!vector)                                                \
        return ERR_NULL_PTR_PARAM(size_t);                                              \
    AS_VEC(type);                                              \
    return RESULT_OK(size_t, v->len);                                           \
}                                               \
                                                \
RESULT(size_t) Vector##type##_Push(Vector* vector, type val)                                             \
{                                               \
    if (!vector)                                                \
        return ERR_NULL_PTR_PARAM(size_t);                                              \
                                                \
    AS_VEC(type);                                              \
    if (v->len == v->total_size) {                                              \
        v->total_size += ARRAY_STEP_SIZE;                                               \
        v->array = realloc(v->array, v->total_size * sizeof(type));                                              \
    }                                           \
    v->array[v->len++] = val;                                           \
                                                \
    return RESULT_OK(size_t, v->len);                                           \
}                                               \
                                                \
RESULT(type) Vector##type##_Pop(Vector* vector)                                          \
{                                               \
    if (!vector)                                                \
        return ERR_NULL_PTR_PARAM(type);                                         \
                                                \
    AS_VEC(type);                                              \
                                                \
    if (v->len == 0)                                            \
        return RESULT_ERR(type, "Empty vector");                                         \
                                                \
    type val = v->array[v->len - 1];                                             \
    memset(&v->array[v->len - 1], 0x00, sizeof(type));                                          \
                                                \
    if (--v->len % ARRAY_STEP_SIZE) {                                           \
        v->total_size -= ARRAY_STEP_SIZE;                                               \
        v->array = realloc(v->array, v->total_size * sizeof(type));                                              \
    }                                           \
                                                \
    return RESULT_OK(type, val);                                         \
}                                               \
                                                \
RESULT(type) Vector##type##_Get(const Vector* vector, size_t index)                                              \
{                                               \
    if (!vector)                                                \
        return ERR_NULL_PTR_PARAM(type);                                         \
    AS_VEC(type);                                              \
    if (v->len < index)                                         \
        return RESULT_ERR(type, "Index out of bounds");                                          \
    return RESULT_OK(type, v->array[index]);                                             \
}                                               \
                                                \
                                                \
Iterator* Vector##type##_ToIter(const Vector* vector)                                           \
{                                               \
    if (!vector)                                                \
        return NULL;                                            \
                                                \
    AS_VEC(type);                                              \
                                                \
    return Iterator_FromArray(v->array, sizeof(type), v->len);                                           \
}




DECLARE_VECTOR_TYPE(uint8_t)
DECLARE_VECTOR_TYPE(uint16_t)
DECLARE_VECTOR_TYPE(uint32_t)
DECLARE_VECTOR_TYPE(uint64_t)
DECLARE_VECTOR_TYPE(int)
DECLARE_VECTOR_TYPE(float)
DECLARE_VECTOR_TYPE(double)

#endif /* __VECTOR_H__ */

