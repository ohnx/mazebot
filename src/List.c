#include "List.h"

List List_new() {
    return calloc(sizeof(List_nonptr), 1);
}

void List_add(List l, void *elem) {
    ListElem a = calloc(sizeof(ListElem_nonptr), 1);
    List_sanity(l);
    a->value = elem;
    a->next = NULL;
    if (l->head == NULL) {
        l->head = a;
        l->tail = a;
    } else {
        (l->tail)->next = a;
        l->tail = a;
    }
    /* incr length */
    l->length++;
}

/* TODO: make List_dup not call List_add */
List List_dup(List l) {
    List n; ListElem cl;
    List_sanity(l);
    n = List_new();
    cl = List_startElem(n);
    while (cl != NULL) {
        List_add(n, ListElem_value(cl));
        cl = ListElem_next(cl);
    }
    return n;
}

void List_delete(List l, List_deleteFunc df) {
    ListElem curr, tmp;
    List_sanity(l);
    curr = List_startElem(l);
    while (curr != NULL) {
        df(curr->value);
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(l);
}

void ListArray_delete(ListArray l, List_deleteFunc df) {
    
}

/* TODO: make List_copy not call List_add */
List List_copy(List l, List_copyFunc cf) {
    List n; ListElem cl;
    List_sanity(l);
    n = List_new();
    cl = List_startElem(n);
    while (cl != NULL) {
        List_add(n, cf(cl));
        cl = ListElem_next(cl);
    }
    return n;
}