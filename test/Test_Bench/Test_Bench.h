
#ifndef S_TEST_BENCH_H
#define S_TEST_BENCH_H

#include <time.h>


#define T_Bench_Run(name, iterations, func, ...)    \
    { \
        size_t t_bench_startTime, t_bench_endTime; \
        t_bench_startTime = T_Bench_GetTimeStamp(); \
        for (size_t t_bench_i = 0U; t_bench_i < iterations; t_bench_i++) (void)func(__VA_ARGS__); \
        t_bench_endTime = T_Bench_GetTimeStamp(); \
        double seconds = (double)(t_bench_endTime - t_bench_startTime) / (double)(CLOCKS_PER_SEC); \
        extern void T_Bench_RegisterResult(const char*, double, size_t); \
        T_Bench_RegisterResult(name, seconds, iterations); \
    }

size_t T_Bench_GetTimeStamp();
void T_Bench_ShowResults(void);


#endif /* S_TEST_BENCH_H */

