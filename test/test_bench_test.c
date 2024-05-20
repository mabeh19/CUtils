#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "Test_Bench/Test_Bench.h"

void t_bench_test(char* buffer, size_t bytes)
{
    memset(buffer, 0xAA, bytes);
}


void t_mat_mul(int w, int h, int A[w][h], int B[w][h])
{
    int C[w][h];
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            C[i][j] = 0;
            for (int k = 0; k < w; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

size_t T_Bench_GetTimeStamp(void)
{
    return clock();
}

void T_Bench_LogResult(const char *msg)
{
    printf("%s", msg);
}

int main()
{
    int A[10][10], B[10][10];
    char buffer[1000];

    memset(A, 0xAA, sizeof(A));
    memset(B, 0x55, sizeof(B));

    T_Bench_Run(t_bench_test, 1000, buffer, 1000);
    T_Bench_Run(t_mat_mul, 1e3, 10, 10, A, B);
    T_Bench_ShowResults();
}

