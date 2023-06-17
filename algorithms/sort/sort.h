

#ifndef __SORT_H__
#define __SORT_H__

#include <stdint.h>
#include <stdbool.h>

#define sort_bubble(array, len, reverse)  _Generic((array), \
                                                     uint8_t *:  sort_bubble_char, \
                                                     uint16_t *: sort_bubble_short, \
                                                     uint32_t *: sort_bubble_int, \
                                                     uint64_t *: sort_bubble_long, \
                                                     float *:    sort_bubble_float, \
                                                     double *:   sort_bubble_double, \
                                                     default:    sort_bubble_int \
                                                     )(array, len, reverse)




void sort_bubble_char(uint8_t *array, uint32_t len, bool reverse);
void sort_bubble_short(uint16_t *array, uint32_t len, bool reverse);
void sort_bubble_int(uint32_t *array, uint32_t len, bool reverse);
void sort_bubble_long(uint64_t *array, uint32_t len, bool reverse);
void sort_bubble_float(float *array, uint32_t len, bool reverse);
void sort_bubble_double(double *array, uint32_t len, bool reverse);

#endif /* __SORT_H__ */
