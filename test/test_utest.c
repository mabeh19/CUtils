#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "uTest/uTest.h"


uTest_CreateGlobalContext();


UTEST_TEST(Base, unit_test)
{
    uTest_AssertNotEqual(100, 100);
}

UTEST_TEST(Base, utest_float)
{
    uTest_AssertNotEqual(3.14F, 3.14F);
}

void uTest_LogResult(const char *msg)
{
    printf("%s\n", msg);
}

unsigned long long uTest_Time(void)
{
    return 1e6 * ((double)clock() / (double)CLOCKS_PER_SEC);
}

int main()
{
    uTest_SetVerbosity(0);

    uTest_Run();

    return 0;
}
