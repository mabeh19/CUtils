#include "uTest/uTest.h"


UTEST_TEST(InnerTests, unit_test2)
{
    uTest_Assert(100 == 100);
}

UTEST_TEST(InnerTests, unit_test3)
{
    const char *str1 = "arst";
    const char *str2 = "arst";

    uTest_AssertMemory((void*)str1, (void*)str2, strlen(str1));
}

UTEST_TEST(InnerTests, unit_test4)
{
    int buf1[4] = {1, 2, 3, 4};
    int buf2[4] = {3, 1, 2, 6};

    uTest_AssertMemory(buf1, buf2, sizeof buf1);
}

UTEST_TEST(InnerTests, unit_test5)
{
    int x, y = 20;
    x = 10;
    uTest_AssertEqual(x, y);
}

