
#include "uTest/uTest.h"



void unit_test(void)
{
    uTest_Assert(100 != 100);
}


int main()
{
    uTest_RegisterTest(unit_test);

    uTest_Run();

    return 0;
}
