

#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <stddef.h>
#include <stdbool.h>

typedef struct Iterator Iterator;

Iterator* Iterator_FromArray(const void* array, size_t elem_size, size_t len);
size_t Iterator_Len(const Iterator* iter);
void Iterator_ForEach(const Iterator* iter, void (*cb)(const void*));
Iterator* Iterator_Map(const Iterator* iter, void* buffer, void (*cb)(void*));
void Iterator_Fold(const Iterator* iter, void* acc, void (*cb)(void*, void*));
void Iterator_Filter(Iterator** iter, bool (*filter)(void*));
void Iterator_BubbleSortBy(Iterator* iter, bool (*comp)(void*, void*));
void Iterator_InsertSortBy(Iterator* iter, bool (*comp)(void*, void*));
void Iterator_Delete(Iterator* iter);

#endif /* __ITERATOR_H__ */
