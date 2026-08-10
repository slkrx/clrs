#ifndef DOUBLY_LINKED
#define DOUBLY_LINKED

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *np;
    int key;
} node;

typedef struct {
    node *nil, *head;
} list;

void init_node(node *n, int key) {
    n->np = NULL;
    n->key = key;
}

node *create_node(int key) {
    node *n = (node *) malloc(sizeof(node));
    init_node(n, key);
    return n;
}

void init_list(list *L) {
    L->nil = create_node(0);
    L->nil->np = NULL;
    L->head = L->nil;
}

list *create_list() {
    list *l = (list *) malloc(sizeof(list));
    init_list(l);
    return l;
};

node *xor(node *a, node *b) {
    return (node *) ((unsigned long) a ^ (unsigned long) b);
}

void list_insert(list *L, node *x) {
    x->np = xor(L->nil, L->head);
    node *nil_prev = xor(L->nil->np, L->head);
    L->nil->np = xor(x, nil_prev);
    node *head_next = xor(L->head->np, L->nil);
    L->head->np = xor(x, head_next);
    L->head = x;
}

node *list_search(list *L, int key) {
    node *x, *prev, *temp;
    x = L->head;
    prev = L->nil;

    while (x != L->nil && x->key != key) {
        temp = x;
        x = xor(x->np, prev);
        prev = temp;
    }
    if (x->key == key)
        return x;
    else
        return NULL;
}

void list_delete(list *L, node *x) {
    node *ptr, *prev, *temp, *prev_prev, *next, *next_next;
    ptr = L->head;
    prev = L->nil;

    while (ptr != L->nil && ptr != x) {
        temp = ptr;
        ptr = xor(ptr->np, prev);
        prev = temp;
    }
    if (ptr == x) {
        prev_prev = xor(prev->np, ptr);
        next = xor(prev, ptr->np);
        if (L->head == x)
            L->head = next;
        next_next = xor(next->np, x);
        prev->np = xor(prev_prev, next);
        next->np = xor(next_next, prev);
        free(x);
    }
}

void print_list(list *L) {
    node *x, *prev, *temp;
    x = L->head;
    prev = L->nil;

    while (x != L->nil) {
        printf("%d ", x->key);
        temp = x;
        x = xor(x->np, prev);
        prev = temp;
    }
    printf("\n");
}

#endif