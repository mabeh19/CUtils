

#ifndef S_TEST_UTEST_H
#define S_TEST_UTEST_H


#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus 
extern "C" {
#endif

typedef void (*uTest_UnitTest)(void);


typedef struct {
    size_t numErrors;
} uTest_Result;

void uTest_LogResult(const char* msg);
void uTest_RegisterTest(uTest_UnitTest test);
uTest_Result uTest_Run(void);


#define uTest_Assert(expr)  uTest_Assert_(expr, __func__, __LINE__, #expr)
void uTest_Assert_(bool expr, const char* funcName, size_t line, const char* exprText);

#define uTest_AssertEqual(p1, p2, size) uTest_AssertEqual_(p1, p2, size, __func__, __LINE__, #p1 " == " #p2)
void uTest_AssertEqual_(void* p1, void* p2, size_t size, const char* funcName, size_t line, const char* exprText);


#ifdef __cplusplus
}
#endif


#endif /* S_TEST_UTEST_H */

