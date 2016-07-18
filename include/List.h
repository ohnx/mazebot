#ifndef __STOUFFE_LIST_H_INC
#define __STOUFFE_LIST_H_INC
#include "util.h"
#define List_length(x) (x->length)
#define ListArray_new(length) calloc(sizeof(List_nonptr), length)
#define ListElem_value(x) (x->value)
#define ListElem_next(x) (x->next)
#define List_startElem(x) (x->head)
#define List_sanity(x) x = (x?x:List_new())

typedef struct _ListElem_nonptr {
    void *value;
    struct _ListElem_nonptr *next;
} ListElem_nonptr;
typedef ListElem_nonptr* ListElem;

typedef struct _List_nonptr {
    ListElem head;
    ListElem tail;
    unsigned int length;
} List_nonptr;
typedef List_nonptr* List;

typedef List* ListArray;

List List_new();
void List_add(List l, void *elem);
List List_dup(List l);
typedef void (*List_deleteFunc)(void *a);
void List_delete(List l, List_deleteFunc df);
void ListArray_delete(ListArray l, List_deleteFunc df);
typedef void *(*List_copyFunc)(void *a);
List List_copy(List l, List_copyFunc cf);
#endif