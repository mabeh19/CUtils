

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

#ifndef UTEST_CODE_SECTION
#define UTEST_CODE_SECTION(s)  __attribute__((section(s)))
#endif

#define UTEST_DEFAULT_DOMAIN_NAME       ""
#define UTEST_LOG_SUCCESS               1
#define UTEST_LOG_DURATION              2
#define UTEST_ERROR_MESSAGE_MAX_LENGTH  256

typedef void (*uTest_UnitTest)(void);


typedef struct uTest_Result {
    size_t numErrors;
} uTest_Result;

struct uTest_Test {
    const char* domain;
    uTest_UnitTest test;
};

struct uTest_Domain {
    const char *name;
    struct uTest_Test *tests;

    struct uTest_Domain *next;
};

struct uTest_Context {
    struct uTest_Domain *domains;
    uTest_Result result;
    struct uTest_Test *startOfTests;
    struct uTest_Test *endOfTests;
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
#define uTest_AssertMemory(p1, p2, size) uTest_AssertMemory_(p1, p2, size, __func__, __LINE__, #p1 " == " #p2)

#if __STDC_VERSION__ >= 201112
#define uTest_AssertEqual(v1, v2)   _Generic((v1),  short:                  uTest_AssertEQShort,      \
                                                    int:                    uTest_AssertEQInt,        \
                                                    long:                   uTest_AssertEQLong,       \
                                                    long long:              uTest_AssertEQLongLong,   \
                                                    unsigned short:         uTest_AssertEQShort,      \
                                                    unsigned int:           uTest_AssertEQInt,        \
                                                    unsigned long:          uTest_AssertEQLong,       \
                                                    unsigned long long:     uTest_AssertEQLongLong,   \
                                                    float:                  uTest_AssertEQFloat,      \
                                                    double:                 uTest_AssertEQDouble,     \
                                                    long double:            uTest_AssertEQLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)

#define uTest_AssertNotEqual(v1, v2)   _Generic((v1),   short:                  uTest_AssertNEQShort,      \
                                                        int:                    uTest_AssertNEQInt,        \
                                                        long:                   uTest_AssertNEQLong,       \
                                                        long long:              uTest_AssertNEQLongLong,   \
                                                        unsigned short:         uTest_AssertNEQShort,      \
                                                        unsigned int:           uTest_AssertNEQInt,        \
                                                        unsigned long:          uTest_AssertNEQLong,       \
                                                        unsigned long long:     uTest_AssertNEQLongLong,   \
                                                        float:                  uTest_AssertNEQFloat,      \
                                                        double:                 uTest_AssertNEQDouble,     \
                                                        long double:            uTest_AssertNEQLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)

#define uTest_AssertGreaterOrEqual(v1, v2) _Generic((v1),   short:                  uTest_AssertGEQShort,      \
                                                            int:                    uTest_AssertGEQInt,        \
                                                            long:                   uTest_AssertGEQLong,       \
                                                            long long:              uTest_AssertGEQLongLong,   \
                                                            unsigned short:         uTest_AssertGEQShort,      \
                                                            unsigned int:           uTest_AssertGEQInt,        \
                                                            unsigned long:          uTest_AssertGEQLong,       \
                                                            unsigned long long:     uTest_AssertGEQLongLong,   \
                                                            float:                  uTest_AssertGEQFloat,      \
                                                            double:                 uTest_AssertGEQDouble,     \
                                                            long double:            uTest_AssertGEQLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)

#define uTest_AssertGreaterThan(v1, v2)   _Generic((v1),    short:                  uTest_AssertGTShort,      \
                                                            int:                    uTest_AssertGTInt,        \
                                                            long:                   uTest_AssertGTLong,       \
                                                            long long:              uTest_AssertGTLongLong,   \
                                                            unsigned short:         uTest_AssertGTShort,      \
                                                            unsigned int:           uTest_AssertGTInt,        \
                                                            unsigned long:          uTest_AssertGTLong,       \
                                                            unsigned long long:     uTest_AssertGTLongLong,   \
                                                            float:                  uTest_AssertGTFloat,      \
                                                            double:                 uTest_AssertGTDouble,     \
                                                            long double:            uTest_AssertGTLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)

#define uTest_AssertLessOrEqual(v1, v2)   _Generic((v1),    short:                  uTest_AssertLEQShort,      \
                                                            int:                    uTest_AssertLEQInt,        \
                                                            long:                   uTest_AssertLEQLong,       \
                                                            long long:              uTest_AssertLEQLongLong,   \
                                                            unsigned short:         uTest_AssertLEQShort,      \
                                                            unsigned int:           uTest_AssertLEQInt,        \
                                                            unsigned long:          uTest_AssertLEQLong,       \
                                                            unsigned long long:     uTest_AssertLEQLongLong,   \
                                                            float:                  uTest_AssertLEQFloat,      \
                                                            double:                 uTest_AssertLEQDouble,     \
                                                            long double:            uTest_AssertLEQLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)

#define uTest_AssertLessThan(v1, v2)   _Generic((v1),   short:                  uTest_AssertLTShort,      \
                                                        int:                    uTest_AssertLTInt,        \
                                                        long:                   uTest_AssertLTLong,       \
                                                        long long:              uTest_AssertLTLongLong,   \
                                                        unsigned short:         uTest_AssertLTShort,      \
                                                        unsigned int:           uTest_AssertLTInt,        \
                                                        unsigned long:          uTest_AssertLTLong,       \
                                                        unsigned long long:     uTest_AssertLTLongLong,   \
                                                        float:                  uTest_AssertLTFloat,      \
                                                        double:                 uTest_AssertLTDouble,     \
                                                        long double:            uTest_AssertLTLongDouble)(v1, v2, #v1, #v2, __LINE__, __func__)
#else
#define uTest_AssertEqual(v1, v2)   uTest_Assert(v1 == v2)
#endif

/*
 * API
 */
#define uTest_CreateGlobalContext()   \
    struct uTest_Domain uTest_defaultDomain = { \
        .name = UTEST_DEFAULT_DOMAIN_NAME, \
        .tests = NULL, \
        .next = NULL, \
    }; \
    extern struct uTest_Test __start_UTEST_TESTS; \
    extern struct uTest_Test __stop_UTEST_TESTS; \
    struct uTest_Domain *uTest_currentDomain = &uTest_defaultDomain; \
    struct uTest_Context uTest_context = { .domains = &uTest_defaultDomain, .startOfTests = &__start_UTEST_TESTS, .endOfTests = &__stop_UTEST_TESTS }; 

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


#define UTEST_TEST(domain, name) UTEST_CODE_SECTION(".utest_functionpath") static const char* domain##_##name##path = #domain #name; void domain##_##name(void); UTEST_CODE_SECTION("UTEST_TESTS") struct uTest_Test domain##_##name##Ptr = { #domain, &domain##_##name }; void domain##_##name(void)

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

#if 0
static inline void uTest_RegisterTest(struct uTest_Domain *domain, struct uTest_Test *testbuffer, uTest_UnitTest test)
{
    struct uTest_Test **t = &domain->tests;
    while (*t) t = &(*t)->next;
    (*t) = testbuffer;
    (*t)->test = test;
    (*t)->next = NULL;
}
#endif

static inline void uTest_RunTest(const char* domain, uTest_UnitTest unitTest)
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
    for (struct uTest_Test *test = uTest_context.startOfTests; test < uTest_context.endOfTests; test++) {
        uTest_RunTest(test->domain, test->test);
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

static inline void uTest_AssertMemory_(void* p1, void* p2, size_t size, const char* funcName, size_t line, const char* exprText)
{
    uTest_context.uut.funcName = funcName;
    if (memcmp(p1, p2, size)) {
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

#define UTEST_ASSERTION(assertion, name, type, fmt) \
    static void uTest_Assert##assertion##name(type v1, type v2, const char *v1Name, const char *v2Name, size_t line, const char *funcName) \
    {                                                                                   \
        uTest_context.uut.funcName = funcName;                                          \
        if (!(v1 UTEST_ASSERTION_TYPE_##assertion v2)) {                                \
            char msg[UTEST_ERROR_MESSAGE_MAX_LENGTH];                                   \
            sprintf(msg, "%s == %s => " fmt " != " fmt, v1Name, v2Name, v1, v2);        \
            uTest_context.uut.error = msg;                                              \
            uTest_context.uut.line = line;                                              \
            longjmp(uTest_context.uut.exitPoint, 1);                                    \
        }                                                                               \
    }

#define UTEST_ASSERTION_TYPE_EQ     ==
#define UTEST_ASSERTION_TYPE_NEQ    !=
#define UTEST_ASSERTION_TYPE_GEQ    >=
#define UTEST_ASSERTION_TYPE_GT     >
#define UTEST_ASSERTION_TYPE_LEQ    <=
#define UTEST_ASSERTION_TYPE_LT     <

#define UTEST_ASSERTIONS(name, type, fmt) \
    UTEST_ASSERTION(EQ, name, type, fmt) \
    UTEST_ASSERTION(NEQ, name, type, fmt) \
    UTEST_ASSERTION(GEQ, name, type, fmt) \
    UTEST_ASSERTION(GT,  name, type, fmt) \
    UTEST_ASSERTION(LEQ, name, type, fmt) \
    UTEST_ASSERTION(LT,  name, type, fmt)

UTEST_ASSERTIONS(Short, short, "%d");
UTEST_ASSERTIONS(Int, int, "%d");
UTEST_ASSERTIONS(Long, long, "%ld");
UTEST_ASSERTIONS(LongLong, long long, "%lld");
UTEST_ASSERTIONS(UnsignedShort, unsigned short, "%u");
UTEST_ASSERTIONS(UnsignedInt, unsigned int, "%u");
UTEST_ASSERTIONS(UnsignedLong, unsigned long, "%lu");
UTEST_ASSERTIONS(UnsignedLongLong, unsigned long long, "%llu");
UTEST_ASSERTIONS(Float, float, "%f");
UTEST_ASSERTIONS(Double, double, "%lf");
UTEST_ASSERTIONS(LongDouble, long double, "%Lf");

#undef UTEST_ASSERTIONS
#undef UTEST_ASSERTION_TYPE_EQ 
#undef UTEST_ASSERTION_TYPE_NEQ
#undef UTEST_ASSERTION_TYPE_GEQ
#undef UTEST_ASSERTION_TYPE_GT 
#undef UTEST_ASSERTION_TYPE_LEQ
#undef UTEST_ASSERTION_TYPE_LT 

#ifdef __cplusplus
}
#endif


#endif /* S_TEST_UTEST_H */

