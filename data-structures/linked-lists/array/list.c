#ifndef ARRAY_LIST
#define ARRAY_LIST

#include <stdlib.h>
#include <stdio.h>

#define key(x) x
#define next(x) x + 1
#define prev(x) x + 2

typedef struct {
    int *data, head, free;
} list;

list *create_list(int size) {
    list *x;
    int i;

    x = (list *) malloc(sizeof(list));
    x->data = (int *) malloc(sizeof(int) * size * 3);
    for (i = 0; i < size - 1; i++)
        x->data[next(i * 3)] = key((i + 1) * 3);
    x->data[next(i * 3)] = -1;
    x->free = 0;
    x->head = -1;
    return x;
}

int allocate_object(list *l) {
    if (l->free == -1) {
        fprintf(stderr, "out of space");
        return -1;
    } else {
        int x = l->free;
        l->free = l->data[next(x)];
        return x;
    }
}

void free_object(list *l, int x) {
    l->data[next(x)] = free;
    l->free = key(x);
}

void list_insert(list *l, int x) {
    int pos;

    pos = allocate_object(l);
    if (pos = -1)
        return;
    l->data[key(x)] = x;
    l->data[next(x)] = l->head;
    l->data[prev(x)] = -1;
    l->head = key(x);
}

#endif