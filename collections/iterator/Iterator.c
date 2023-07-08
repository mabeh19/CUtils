#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Iterator.h"

typedef struct Iterator_t {
    void* val;
    size_t elem_size;
    struct Iterator_t* next;
} Iterator_t;

Iterator* Iterator_FromArray(const void* array, size_t elem_size, size_t len)
{
    Iterator_t* start = malloc(sizeof(Iterator_t)); 
    Iterator_t* iter = start;
    for (int i = 0; i < len; i++) {
        iter->val = (void*)(array + elem_size * i);
        iter->elem_size = elem_size;

        if (i < (len - 1)) {
            iter->next = malloc(sizeof(Iterator_t));
            iter = iter->next;
        }
        else
            iter->next = NULL;
    }

    return (Iterator*)start;
}

void Iterator_Delete(Iterator *iter)
{
    Iterator_t *i = (Iterator_t*)iter;
    while (i) {
        Iterator_t *next = i->next;
        free(i);
        i = next;
    }
}

void Iterator_ForEach(const Iterator* iter, void (*cb)(const void*))
{
    Iterator_t* i = (Iterator_t*)iter;
    while(i) {
        cb(i->val);
        i = i->next;
    }
}

Iterator* Iterator_Map(const Iterator* iter, void* buffer, void (*cb)(void*))
{
size_t j = 0;
    Iterator_t* new_iter = malloc(sizeof(Iterator_t));
    Iterator_t* n_i = new_iter;
    Iterator_t* i = (Iterator_t*)iter;

    while(i) {
        n_i->val = (buffer + i->elem_size * j);
        n_i->elem_size = i->elem_size;
        memcpy(n_i->val, i->val, i->elem_size);
        cb(n_i->val);

        i = i->next;

        if (i) {
            n_i->next = malloc(sizeof(Iterator_t));
            n_i = n_i->next;
        } else {
            n_i->next = NULL;
        }

        j++;
    }

    return (Iterator*)new_iter;
}


size_t Iterator_Len(const Iterator* iter)
{
    if (!iter)
        return 0;

    Iterator_t* i = (Iterator_t*)iter;
    size_t len = 0;

    while (i) {
        ++len;
        i = i->next;
    }

    return len;
}

void Iterator_Fold(const Iterator* iter, void* acc, void (*cb)(void*, void*))
{
    Iterator_t* i = (Iterator_t*)iter;
    while (i) {
        cb(acc, i->val);
        i = i->next;
    }
}


void Iterator_Filter(Iterator** iter, bool (*filter)(void*))
{
    if (!iter || !filter) {
        return;
    }

    Iterator_t** iterator = (Iterator_t**)iter;
    Iterator_t* first = *iterator;

    while (!filter(first->val)) {
        Iterator_t* toFree = first;
        first = first->next;
        *iterator = first;

        free(toFree);
    }

    Iterator_t* i_prev = first;
    Iterator_t* i = first->next;
    Iterator_t* i_next = i->next;


    while (i && i_next) {
        if (!filter(i->val)) {
            i_prev->next = i_next;
            free(i);
        } else {
            i_prev = i_prev->next;
        }
        i = i_next;
        i_next = i_next->next;
    }
}


static void Iterator_Swap(Iterator_t* iter1, Iterator_t* iter2)
{
    void* tmpIterVal = iter1->val;
    iter1->val = iter2->val;
    iter2->val = tmpIterVal;
}

static void Iterator_InsertAfter(Iterator_t* iter1, Iterator_t* iter2)
{

}

/*
* Currently implemented as a bubble sort
*/
void Iterator_BubbleSortBy(Iterator* iter, bool (*comp)(void*, void*))
{
    if (!iter || !comp)
        return;

    Iterator_t* i1 = (Iterator_t*)iter;

    while(i1) {   
        Iterator_t* i2 = i1->next;

        while(i2) {
            if (comp(i1->val, i2->val)) {
                Iterator_Swap(i1, i2);
            }
            i2 = i2->next;
        }
        i1 = i1->next;
    }
}
