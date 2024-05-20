
#ifndef S_TEST_BENCH_H
#define S_TEST_BENCH_H

#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define T_BENCH_LOG_RESULT_BUFFER_SIZE 1024

#define T_Bench_Run(func, iterations, ...)    \
    { \
        size_t t_bench_startTime, t_bench_endTime; \
        t_bench_startTime = T_Bench_GetTimeStamp(); \
        for (size_t t_bench_i = 0U; t_bench_i < iterations; t_bench_i++) (void)func(__VA_ARGS__); \
        t_bench_endTime = T_Bench_GetTimeStamp(); \
        double seconds = (double)(t_bench_endTime - t_bench_startTime) / (double)(CLOCKS_PER_SEC); \
        static Test_Bench_Result result; \
        T_Bench_RegisterResult(&result, #func, seconds, iterations); \
    }


/*
 * User implemented
 */
size_t T_Bench_GetTimeStamp();
void T_Bench_LogResult(const char *msg);

typedef struct Test_Bench_Result {
    const char* name;
    double seconds;
    size_t iterations;

    struct Test_Bench_Result *next;
} Test_Bench_Result;

struct tb_results {
    Test_Bench_Result *results;
} tb_results;

static inline void T_Bench_RegisterResult(Test_Bench_Result *resbuf, const char* name, double seconds, size_t iterations)
{
    resbuf->name = name;
    resbuf->name = name;
    resbuf->seconds = seconds;
    resbuf->iterations = iterations;
    resbuf->next = NULL;

    Test_Bench_Result **res = &tb_results.results;
    while (*res) 
        res = &(*res)->next;
    *res = resbuf;
}

static inline void T_Bench_ShowResults(void)
{
    static char resultBuffer[T_BENCH_LOG_RESULT_BUFFER_SIZE];
    int offset = 0;
    offset += snprintf(resultBuffer, sizeof resultBuffer, "%s", "================================ TEST BENCH RESULTS ==================================\n");

    for (Test_Bench_Result *res = tb_results.results; res != NULL; res = res->next) { 
        offset += snprintf(resultBuffer + offset, sizeof resultBuffer - offset, "[%-32s] ==> %'20.6f ms (%'10lu iterations)\n", res->name, 1e3 * res->seconds, res->iterations);
    }
    offset += snprintf(resultBuffer + offset, sizeof resultBuffer - offset, "======================================================================================\n");

    T_Bench_LogResult(resultBuffer);
}


#ifdef __cplusplus
}
#endif

#endif /* S_TEST_BENCH_H */

