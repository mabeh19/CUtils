#include <stdio.h>
#include <stdlib.h>
#include "Results.h"
#include "linked_list/LinkedList.h"
#include "vector/Vector.h"
#include "iterator/Iterator.h"

typedef struct {
    double x;
    int y;
} Foo_t;

DEF_RESULT(Foo_t);
DECLARE_VECTOR_TYPE(Foo_t);
DEFINE_VECTOR_TYPE(Foo_t);

void test_iter_filter(void);
void test_iter_map(void);

void print(const void* val)
{
    if (!val) {
        printf("NULL pointer encountered\n");
        return;
    }

    printf("%d\n", *(int*)val);
}

bool reverse(void* v1, void* v2)
{
    Foo_t *i1 = v1, *i2 = v2;

    return i1->x < i2->x;
}

Vector* construct_vec(size_t len)
{
    Vector* vec = Vector_New(int);

    for (size_t i = 0; i < len; i++) {
        Vector_Push(int, vec, i);
    }

    return vec;
}

int main()
{
    test_iter_filter();
    test_iter_map();
    
    return 0;
}

bool test_filter(void* val)
{
    return *(int*)val > 50;
}

void test_print_int(const void* val)
{
    printf("%d\n", *(int*)val);
}

void test_iter_filter(void)
{
    Vector* vec = construct_vec(100);
    Iterator* iter = Vector_ToIter(int, vec);

    Iterator_ForEach(iter, test_print_int);
    Iterator_Filter(&iter, test_filter);
    
    Iterator_ForEach(iter, test_print_int);

    Iterator_Delete(iter);
    Vector_Delete(int, vec);
}


void test_double(void* val)
{
    int* ival = val;
    *ival *= 2;
}


void test_iter_map(void)
{
    void* buffer = malloc(10 * sizeof(int));
    Vector* vec = construct_vec(10);
    Iterator* iter = Vector_ToIter(int, vec);
    Iterator* iterDoubled = Iterator_Map(iter, buffer, test_double);
 
    Iterator_ForEach(iter, print);
    Iterator_ForEach(iterDoubled, print);

    Iterator_Delete(iter);
    Iterator_Delete(iterDoubled);
    Vector_Delete(int, vec);
    free(buffer);
}
