#include <stdlib.h>

#include "LinkedList.h"

#define AS_INTERNAL()  LinkedList_t* _l = (LinkedList_t*)list

typedef struct LinkedListElement {
    LinkedListElement val;
    struct LinkedListElement* next;
    struct LinkedListElement* prev;
} LinkedListElement_t;

typedef struct {
    size_t len;
    LinkedListElement_t* first;
    LinkedListElement_t* last;
} LinkedList_t;

LinkedList* LinkedList_New(void)
{
    LinkedList_t* list = malloc(sizeof(LinkedList_t));

    if (!list) {
        return NULL;
    }

    list->len = 0;
    list->first = NULL;
    list->last = NULL;

    return (LinkedList*)list;
}


RESULT(LinkedListElement) LinkedList_Get(const LinkedList* list, size_t index)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(LinkedListElement);

    AS_INTERNAL();

    if (!_l->first)
        return RESULT_ERR(LinkedListElement, "Empty list");
    else if (_l->len < index)
        return RESULT_ERR(LinkedListElement, "Index out of range");

    LinkedListElement_t* elem = _l->first;
    for (size_t i = 0; i < index; i++)
        elem = elem->next;

    return RESULT_OK(LinkedListElement, elem->val);
}


RESULT(size_t) LinkedList_Len(const LinkedList* list)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(size_t);

    return RESULT_OK(size_t, ((LinkedList_t*)list)->len);
}

RESULT(size_t) LinkedList_Push(LinkedList* list, LinkedListElement val)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(size_t);

    AS_INTERNAL();

    LinkedListElement_t* new_elem = malloc(sizeof(LinkedListElement_t));

    if (!new_elem) {
        return RESULT_ERR(size_t, "Unable to allocate new element");
    }

    new_elem->val = val;
    new_elem->next = NULL;
    new_elem->prev = NULL;

    if (!_l->first) {
        _l->first = new_elem;
        _l->len++;
    } else {
        LinkedListElement_t* elem = _l->first;
        while (elem->next) elem = elem->next;
        elem->next = new_elem;
        new_elem->prev = elem;
        _l->len++;
    }

    _l->last = new_elem;

    return RESULT_OK(size_t, _l->len);
}

RESULT(LinkedListElement) LinkedList_Pop(LinkedList* list)
{
    if (!list)
        return ERR_NULL_PTR_PARAM(LinkedListElement);

    AS_INTERNAL();

    if (!_l->first) {
        return RESULT_ERR(LinkedListElement, "Empty list");
    }


    LinkedListElement_t* lastElem = _l->last;
    LinkedListElement val = lastElem->val;
    _l->last = lastElem->prev;
    free(lastElem);
    if (_l->last) {
        _l->last->next = NULL;
    } 
    else {
        _l->first = NULL;
    }
    _l->len--;

    return RESULT_OK(LinkedListElement, val);
}

