#include <stdlib.h>

#include "LinkedList.h"

#define AS_INTERNAL()  LinkedList_t* _l = (LinkedList_t*)list

typedef struct LinkedListElement {
    int val;
    struct LinkedListElement* next;
} LinkedListElement;

typedef struct {
    size_t len;
    LinkedListElement* first;
    LinkedListElement* last;
} LinkedList_t;

LinkedList* LinkedList_New(void)
{
    LinkedList_t* list = malloc(sizeof(LinkedList_t));

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

    return (LinkedList*)list;
}


RESULT(int) LinkedList_Get(const LinkedList* list, size_t index)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(int);

    AS_INTERNAL();

    if (!_l->first)
        return RESULT_ERR(int, "Empty list");
    else if (_l->len < index)
        return RESULT_ERR(int, "Index out of range");

    LinkedListElement* elem = _l->first;
    for (size_t i = 0; i < index; i++)
        elem = elem->next;

    return RESULT_OK(int, elem->val);
}


RESULT(size_t) LinkedList_Len(const LinkedList* list)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(size_t);

    return RESULT_OK(size_t, ((LinkedList_t*)list)->len);
}

RESULT(size_t) LinkedList_Push(LinkedList* list, int val)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(size_t);

    AS_INTERNAL();

    LinkedListElement* new_elem = malloc(sizeof(LinkedListElement));
    new_elem->val = val;

    if (!_l->first) {
        _l->first = new_elem;
        _l->len++;
    } else {
        LinkedListElement* elem = _l->first;
        while (elem->next) elem = elem->next;
        elem->next = new_elem;
        _l->len++;
    }

    _l->last = new_elem;

    return RESULT_OK(size_t, _l->len);
}

RESULT(int) LinkedList_Pop(LinkedList* list)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(int);

    AS_INTERNAL();

    if (!_l->first) {
        return RESULT_ERR(int, "Empty list");
    }

    LinkedListElement* last = _l->first;
    while (last->next->next) last = last->next;
    int val = last->next->val;
    free(last->next);
    last->next = NULL;
    _l->len--;

    return RESULT_OK(int, val);
}

