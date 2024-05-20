#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "uTest/uTest.h"


uTest_CreateGlobalContext();

void register_extra_tests(void);


void unit_test(void)
{
    uTest_Assert(100 != 100);
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
    uTest_Register(unit_test);
    uTest_SetVerbosity(UTEST_LOG_SUCCESS | UTEST_LOG_DURATION);

    register_extra_tests();

    uTest_Run();

    return 0;
}
