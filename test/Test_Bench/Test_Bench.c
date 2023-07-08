#include <stdio.h>
#include <string.h>

#include "../../datatypes/string/cstring.h"
#include "../../collections/vector/Vector.h"


typedef struct Test_Bench_Result {
    String* name;
    double seconds;
    size_t iterations;
} Test_Bench_Result;

DEF_RESULT(Test_Bench_Result);
DECLARE_VECTOR_TYPE(Test_Bench_Result)
DEFINE_VECTOR_TYPE(Test_Bench_Result)


static void T_Bench_PrintResult(const void* result);
static void T_Bench_CleanUp(const void *test);

Vector* test_bench_results = NULL;



void T_Bench_RegisterResult(const char* name, double result, size_t iterations)
{
    if (test_bench_results == NULL) {
        test_bench_results = Vector_New(Test_Bench_Result);
    }
    struct Test_Bench_Result tbenchResult = {
        .name = String_new(name),
        .seconds = result, 
        .iterations = iterations
    };
    Vector_Push(Test_Bench_Result, test_bench_results, tbenchResult);
}


void T_Bench_ShowResults(void)
{
    Iterator* results = Vector_ToIter(Test_Bench_Result, test_bench_results);
    
    printf("================================ TEST BENCH RESULTS ==================================\n");
    Iterator_ForEach(results, T_Bench_PrintResult);
    printf("======================================================================================\n");

    Iterator_ForEach(results, T_Bench_CleanUp);

    Iterator_Delete(results);
    Vector_Delete(Test_Bench_Result, test_bench_results);
}


static void T_Bench_PrintResult(const void* result)
{
    struct Test_Bench_Result* res = (struct Test_Bench_Result*)result;

    printf("[%-32s] ==> %'20.6f ms (%'10lu iterations)\n", res->name->as_raw, 1e3 * res->seconds, res->iterations);
}


static void T_Bench_CleanUp(const void *test)
{
    struct Test_Bench_Result *t = (struct Test_Bench_Result*)test;
    
    String_delete(t->name);
}
