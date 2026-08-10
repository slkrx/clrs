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
    node *head;
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
    L->head = NULL;
}

list *create_list() {
    list *l = (list *) malloc(sizeof(list));
    init_list(l);
    return l;
};

void list_insert(list *L, node *x) {
    x->next = L->head;
    L->head = x;
}

node *list_search(list *L, int key) {
    node *x = L->head;
    while (x != NULL && x->key != key)
        x = x->next;
    return x;
}

void list_delete(list *L, node *x) {
    if (L->head == x) {
        L->head = x->next;
        return;
    }
    node *y = L->head;
    while (y != NULL && y->next != x)
        y = y->next;
    if (y != NULL) {
        y->next = x->next;
        free(x);
    }
}

void print_list(list *L) {
    node *x = L->head;
    while (x != NULL) {
        printf("%d%c", x->key, x->next == NULL ? '\n' : ' ');
        x = x->next;
    }
}

void reverse_list(list *L) {
    node *lead, *follow, *temp;

    lead = L->head;
    follow = NULL;

    while (lead != NULL) {
        temp = lead->next;
        lead->next = follow;
        follow = lead;
        lead = temp;
    }

    L->head = follow;
}

#endif