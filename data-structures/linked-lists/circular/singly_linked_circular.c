#ifndef SINGLY_LINKED
#define SINGLY_LINKED

#define NULL 0
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int key;
} node;

typedef struct {
    node *nil;
} list;

void init_node(node *n, int key) {
    n->next = NULL;
    n->key = key;
}

node *create_node(int key) {
    node *n = (node *) malloc(sizeof(node));
    init_node(n, key);
    return n;
}

void init_list(list *L) {
    L->nil = create_node(NULL);
    L->nil->next = L->nil;
}

list *create_list() {
    list *l = (list *) malloc(sizeof(list));
    init_list(l);
    return l;
};

void list_insert(list *L, node *x) {
    x->next = L->nil->next;
    L->nil->next = x;
}

node *list_search(list *L, int key) {
    node *x = L->nil->next;
    while (x != L->nil && x->key != key)
        x = x->next;
    return x;
}

void list_delete(list *L, node *x) {
    node *ptr = L->nil;
    while (ptr->next != x && ptr->next != L->nil)
        ptr = ptr->next;
    if (ptr->next == x) {
        ptr->next = x->next;
        free(x);
    }
}

void print_list(list *L) {
    node *x = L->nil->next;
    while (x != L->nil) {
        printf("%d%c", x->key, x->next == L->nil ? '\n' : ' ');
        x = x->next;
    }
}

#endif