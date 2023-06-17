#include <stdio.h>
/*
#include <stdarg.h>
#include <stddef.h>
*/

#include "tests/tests.h"

int main()
{
    #ifdef TEST
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(bubble_sort_test),
    };

    cmocka_run_group_tests(tests, NULL, NULL);

    #endif
}
