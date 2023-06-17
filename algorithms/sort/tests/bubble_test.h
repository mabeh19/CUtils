
#ifndef __BUBBLE_TEST_H__
#define __BUBBLE_TEST_H__


#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../sort.h"

inline static void bubble_sort_test(void **state)
{
        (void) state;

        uint8_t sorted_array[5] = {1, 2, 3, 4, 5};
        uint8_t sorted_reverse_array[5] = {5, 4, 3, 2, 1};
        uint8_t rand_array[5] = {4, 2, 5, 1, 3};

        uint32_t sorted_int_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        uint32_t rand_int_array[10] = {3, 2, 5, 8, 1, 6, 9, 4, 10, 7};

        sort_bubble(rand_array, sizeof(rand_array) / sizeof(uint8_t), false);
        assert_memory_equal(sorted_array, rand_array, sizeof(rand_array));
        
        sort_bubble(rand_array, sizeof(rand_array) / sizeof(uint8_t), true);
        assert_memory_equal(sorted_reverse_array, rand_array, sizeof(rand_array));

        sort_bubble(rand_int_array, sizeof(rand_int_array) / sizeof(uint32_t), false);
        assert_memory_equal(rand_int_array, sorted_int_array, sizeof(rand_int_array));
}

#endif /* __BUBBLE_TEST_H__ */
