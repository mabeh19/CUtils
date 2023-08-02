

#include <setjmp.h>
#include <string.h>
#include <stdio.h>
#include "uTest.h"
#include "../../collections/linked_list/LinkedList.h"



struct uTest_Context {
    LinkedList *tests;
    struct {
        jmp_buf exitPoint;
        const char *funcName;
        const char *error;
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
static char logMsg[200];
static uTest_Result result = { 0 };
static RESULT(LinkedListElement) llRes;
static uTest_UnitTest test;

    while ((llRes = LinkedList_Pop(utest_context.tests)).result == OK(LinkedListElement)) {
        int ret = setjmp(utest_context.uut.exitPoint);
        test = llRes.val;

        if (ret == 0) {
            test();
            snprintf(logMsg, sizeof(logMsg), "[SUCCESS] in %s", utest_context.uut.funcName);
        } else if (ret > 0){
            result.numErrors++;
            snprintf(logMsg, sizeof(logMsg), "[ERROR  ] in %s => %s", utest_context.uut.funcName, utest_context.uut.error);
        }

        uTest_LogResult(logMsg);
    }

    return result;
}


void uTest_Assert_(bool expr, const char *name, const char *exprText)
{
    utest_context.uut.funcName = name;
    if (!expr) {
        utest_context.uut.error = exprText;
        longjmp(utest_context.uut.exitPoint, 1);
    }
}


void uTest_AssertEqual_(void *p1, void *p2, size_t size, const char *name)
{
static char errorText[20];

    if (memcmp(p1, p2, size)) {
        snprintf(errorText, sizeof(errorText), "%p[%lu] != %p[%lu]", p1, size, p2, size);
        utest_context.uut.funcName = name;
        utest_context.uut.error = errorText;
        longjmp(utest_context.uut.exitPoint, 1);
    }
}


