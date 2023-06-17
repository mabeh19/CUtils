

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>
#include "../Results.h"

typedef struct{} LinkedList;

LinkedList* LinkedList_New(void);
RESULT(int) LinkedList_Get(const LinkedList* list, size_t index);
RESULT(size_t) LinkedList_Len(const LinkedList* list);
RESULT(size_t) LinkedList_Push(LinkedList* list, int val);
RESULT(int) LinkedList_Pop(LinkedList* list);

#endif
