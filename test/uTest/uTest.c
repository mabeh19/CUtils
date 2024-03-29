

#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include "uTest.h"
#include "../../collections/linked_list/LinkedList.h"


void uTest_RunTest(void* unitTest);


struct uTest_Context {
    LinkedList *tests;
    uTest_Result result;
    struct {
        jmp_buf exitPoint;
        const char *funcName;
        const char *error;
        size_t line;
    } uut;
} utest_context;



void uTest_RegisterTest(uTest_UnitTest test)
{
    if (utest_context.tests == NULL) {
        utest_context.tests = LinkedList_New();
    }

    LinkedList_Push(utest_context.tests, test);
}


uTest_Result uTest_Run(void)
{
    LinkedList_ForEach(utest_context.tests, uTest_RunTest);

    return utest_context.result;
}


void uTest_Assert_(bool expr, const char *name, size_t line, const char *exprText)
{
    utest_context.uut.funcName = name;
    if (!expr) {
        utest_context.uut.error = exprText;
        utest_context.uut.line = line;
        longjmp(utest_context.uut.exitPoint, 1);
    }
}


void uTest_AssertEqual_(void* p1, void* p2, size_t size, const char* funcName, size_t line, const char* exprText)
{
static char errorText[20];

    if (memcmp(p1, p2, size)) {
        utest_context.uut.funcName = funcName;
        utest_context.uut.error = exprText;
        utest_context.uut.line = line;
        longjmp(utest_context.uut.exitPoint, 1);
    }
}


void uTest_RunTest(void* unitTest)
{
static char logMsg[200];
    uTest_UnitTest test = unitTest;
    int ret = setjmp(utest_context.uut.exitPoint);
    

    if (ret == 0) {
        test();
        snprintf(logMsg, sizeof(logMsg), "[SUCCESS] in %s", utest_context.uut.funcName);
    }
    else if (ret > 0) {
        utest_context.result.numErrors++;
        snprintf(logMsg, sizeof(logMsg), "[ERROR  ] in %s:%zu => %s", utest_context.uut.funcName, utest_context.uut.line, utest_context.uut.error);
    }

    uTest_LogResult(logMsg);
}