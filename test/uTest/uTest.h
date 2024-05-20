

#ifndef S_TEST_UTEST_H
#define S_TEST_UTEST_H


#include <stddef.h>
#include <stdbool.h>
#include <setjmp.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus 
extern "C" {
#endif


#define UTEST_DEFAULT_DOMAIN_NAME   ""
#define UTEST_LOG_SUCCESS       1
#define UTEST_LOG_DURATION      2

typedef void (*uTest_UnitTest)(void);


typedef struct uTest_Result {
    size_t numErrors;
} uTest_Result;

struct uTest_Test {
    uTest_UnitTest test;
    struct uTest_Test *next;
};

struct uTest_Domain {
    const char *name;
    struct uTest_Test *tests;

    struct uTest_Domain *next;
};

struct uTest_Context {
    struct uTest_Domain *domains;
    uTest_Result result;
    struct uTest_Options {
        int verbosity;
    } opts;
    struct {
        jmp_buf exitPoint;
        const char *funcName;
        const char *error;
        size_t line;
    } uut;
};



/*
 * Assertions 
 */
#define uTest_Assert(expr)  uTest_Assert_(expr, __func__, __LINE__, #expr)
#define uTest_AssertEqual(p1, p2, size) uTest_AssertEqual_(p1, p2, size, __func__, __LINE__, #p1 " == " #p2)

/*
 * API
 */
#define uTest_CreateGlobalContext()   \
    struct uTest_Domain uTest_defaultDomain = { \
        .name = UTEST_DEFAULT_DOMAIN_NAME, \
        .tests = NULL, \
        .next = NULL, \
    }; \
    struct uTest_Domain *uTest_currentDomain = &uTest_defaultDomain; \
    struct uTest_Context uTest_context = { .domains = &uTest_defaultDomain }; 

#define uTest_Register(test)    do { static struct uTest_Test newtest; uTest_RegisterTest(uTest_currentDomain, &newtest, test); } while (0)
#define uTest_Domain(domainName, ...)      do { \
        static struct uTest_Domain domain; \
        domain.name = domainName; \
        domain.tests = NULL; \
        domain.next = NULL; \
        struct uTest_Domain *outerDomain = uTest_currentDomain; \
        uTest_currentDomain = &domain; \
        uTest_RegisterDomain(&domain); \
        static struct uTest_Test testBuffers[sizeof((uTest_UnitTest[]){__VA_ARGS__}) / sizeof(uTest_UnitTest)]; \
        uTest_UnitTest unitTests[] = { __VA_ARGS__ }; \
        for (long i = 0; i < (sizeof testBuffers / sizeof testBuffers[0]); i++) { \
             uTest_RegisterTest(&domain, testBuffers + i, unitTests[i]); \
        } \
        uTest_currentDomain = outerDomain; \
    } while (0)


static inline uTest_Result uTest_Run(void);

static inline void uTest_SetVerbosity(int level);

/*
 * User implemented
 */
void uTest_LogResult(const char* msg);
unsigned long long uTest_Time(void);




/*
 * Implementation
 */
extern struct uTest_Context uTest_context;
extern struct uTest_Domain uTest_defaultDomain;
extern struct uTest_Domain *uTest_currentDomain;

static inline void uTest_RegisterTest(struct uTest_Domain *domain, struct uTest_Test *testbuffer, uTest_UnitTest test)
{
    struct uTest_Test **t = &domain->tests;
    while (*t) t = &(*t)->next;
    (*t) = testbuffer;
    (*t)->test = test;
    (*t)->next = NULL;
}

static inline void uTest_RunTest(const char *domain, uTest_UnitTest unitTest)
{
static char logMsg[200];
    uTest_UnitTest test = unitTest;
    unsigned long long endTime, startTime = uTest_Time();
    int offset = 0;

    if (setjmp(uTest_context.uut.exitPoint) == 0) {
        test();
        endTime = uTest_Time();
        if (uTest_context.opts.verbosity & UTEST_LOG_SUCCESS) {
            offset = snprintf(logMsg, sizeof(logMsg), "[SUCCESS] in %s::%s", domain, uTest_context.uut.funcName);
            if (uTest_context.opts.verbosity & UTEST_LOG_DURATION)
                snprintf(logMsg + offset, sizeof logMsg - offset, " (duration: %.3f)", ((double)endTime - (double)startTime) / 1000.0);
        }
        else
            logMsg[0] = 0;
    }
    else {
        endTime = uTest_Time();
        uTest_context.result.numErrors++;
        offset = snprintf(logMsg, sizeof(logMsg), "[ERROR  ] in %s::%s:%zu => %s", domain, uTest_context.uut.funcName, uTest_context.uut.line, uTest_context.uut.error);
        if (uTest_context.opts.verbosity & UTEST_LOG_DURATION) 
                snprintf(logMsg + offset, sizeof logMsg - offset, " (duration: %.3f)", ((double)endTime - (double)startTime) / 1000.0);
    }


    if (logMsg[0])
        uTest_LogResult(logMsg);
}

static inline uTest_Result uTest_Run(void)
{
    for (struct uTest_Domain *d = uTest_context.domains; d != NULL; d = d->next) {
        for (struct uTest_Test *t = d->tests; t != NULL; t = t->next) {
            uTest_RunTest(d->name, t->test);
        }
    }

    return uTest_context.result;
}


static inline void uTest_Assert_(bool expr, const char* funcName, size_t line, const char* exprText)
{
    uTest_context.uut.funcName = funcName;
    if (!expr) {
        uTest_context.uut.error = exprText;
        uTest_context.uut.line = line;
        longjmp(uTest_context.uut.exitPoint, 1);
    }
}

static inline void uTest_AssertEqual_(void* p1, void* p2, size_t size, const char* funcName, size_t line, const char* exprText)
{
    if (memcmp(p1, p2, size)) {
        uTest_context.uut.funcName = funcName;
        uTest_context.uut.error = exprText;
        uTest_context.uut.line = line;
        longjmp(uTest_context.uut.exitPoint, 1);
    }
}

static inline void uTest_SetVerbosity(int level)
{
    uTest_context.opts.verbosity = (level < 0) ? 0 : level;
}

static inline void uTest_RegisterDomain(struct uTest_Domain *domain)
{
    struct uTest_Domain **d = &uTest_context.domains;
    while (*d) d = &(*d)->next;
    *d = domain;
}


#ifdef __cplusplus
}
#endif


#endif /* S_TEST_UTEST_H */

