#include "uTest/uTest.h"


void unit_test2(void)
{
    uTest_Assert(100 == 100);
}

void unit_test3(void)
{
    const char *str1 = "arst";
    const char *str2 = "arst";

    uTest_AssertEqual((void*)str1, (void*)str2, strlen(str1));
}

void unit_test4(void)
{
    int buf1[4] = {1, 2, 3, 4};
    int buf2[4] = {3, 1, 2, 6};

    uTest_AssertEqual(buf1, buf2, sizeof buf1);
}

void register_extra_tests(void)
{
    uTest_Domain("Inner Tests",
        unit_test2,
        unit_test3,
        unit_test4,
    );
}
