#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>
#include "singly_linked.c"

typedef struct {
    list *data;
} stack;

void init_stack(stack *S) {
    S = (stack *) malloc(sizeof(stack));
    S->data = (list *) malloc(sizeof(list));
    init_list(S->data);
}

stack *create_stack() {
    stack *S;
    init_stack(S);
    return S;
}

int stack_empty(stack *S) {
    return S->data->head == NULL;
}

void stack_push(stack *S, int x) {
    list_insert(S->data, create_node(x));
}

int stack_pop(stack *S) {
    if (stack_empty(S))
        fprintf(stderr, "underflow");
    else {
        int key = S->data->head->key;
        list_delete(S->data, S->data->head);
        return key;
    }
    return 0;
}

#endif