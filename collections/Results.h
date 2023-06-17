
#ifndef __RESULT_H__
#define __RESULT_H__

#include <stddef.h>
#include <stdint.h>

#define DEF_RESULT(T)                   \
typedef struct {                        \
        enum {                          \
                Ok_##T,                 \
                Err_##T                 \
        } result;                       \
                                        \
        union {                         \
                T val;                  \
                const char* error;      \
        };                              \
} Result_##T

#define RESULT(T)  Result_##T
#define OK(T)   Ok_##T
#define ERR(T)  Err_##T
#define RESULT_OK(T, v)         ((RESULT(T)) { .result = OK(T), .val = v })
#define RESULT_ERR(T, e)        ((RESULT(T)) { .result = ERR(T), .error = e })
#define ERR_NULL_PTR_PARAM(T)      RESULT_ERR(T, "NULL pointer passed to function")


// Ints
DEF_RESULT(uint8_t);
DEF_RESULT(char);
DEF_RESULT(uint16_t);
DEF_RESULT(short);
DEF_RESULT(uint32_t);
DEF_RESULT(int);
DEF_RESULT(uint64_t);
DEF_RESULT(long);
DEF_RESULT(size_t);

// Floats
DEF_RESULT(float);
DEF_RESULT(double);

#endif 
