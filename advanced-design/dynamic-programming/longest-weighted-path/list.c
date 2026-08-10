#ifndef LIST
#define LIST

#include <stdlib.h>

typedef struct {
    int source, target;
    float weight;
} edge;

typedef struct node {
    struct node *next;
    edge *key;
} node;

typedef struct {
    node *head;
} list;

void list_insert(list *L, node *x) {
    x->next = L->head;
    L->head = x;
}

edge *create_edge(int source, int target, int weight) {
    edge *e;

    e = (edge *) malloc(sizeof(edge));
    e->source = source;
    e->target = target;
    e->weight = weight;
    return e;
}

node *create_node(edge *key) {
    node *x;

    x = (node *) malloc(sizeof(node));
    x->key = key;
    x->next = NULL;
    return x;
}

list *create_list() {
    list *L;

    L = (list*) malloc(sizeof(list));
    L->head = NULL;
    return L;
}

#endif