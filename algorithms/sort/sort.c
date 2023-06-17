
#include "sort.h"

#define swap(elem1, elem2)  _Generic((elem1), \
                                             uint8_t *:  swap_char, \
                                             uint16_t *: swap_short, \
                                             uint32_t *: swap_int, \
                                             uint64_t *: swap_long, \
                                             float *:    swap_float, \
                                             double *:   swap_double \
                                             )(elem1, elem2)

void swap_char(uint8_t *elem1, uint8_t *elem2)
{
        uint8_t tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void swap_short(uint16_t *elem1, uint16_t *elem2)
{
        uint16_t tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void swap_int(uint32_t *elem1, uint32_t *elem2)
{
        uint32_t tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void swap_long(uint64_t *elem1, uint64_t *elem2)
{
        uint64_t tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void swap_float(float *elem1, float *elem2)
{
        float tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void swap_double(double *elem1, double *elem2)
{
        double tmp = *elem2;
        *elem2 = *elem1;
        *elem1 = tmp;
}

void sort_bubble_char(uint8_t *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}

void sort_bubble_short(uint16_t *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}

void sort_bubble_int(uint32_t *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}

void sort_bubble_long(uint64_t *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}

void sort_bubble_float(float *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}

void sort_bubble_double(double *array, uint32_t len, bool reverse)
{
        uint32_t swaps = 1;

        while ( swaps > 0 ) {
                swaps = 0;
                for ( uint32_t i = 1; i < len; ++i ) {
                        if ( reverse ) {
                                if ( array[i] > array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        } else {
                                if ( array[i] < array[i - 1] ) {
                                        swap(&array[i], &array[i - 1]);
                                        ++swaps;
                                }
                        }
                }
        }
}
