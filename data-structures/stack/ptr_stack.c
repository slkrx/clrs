#ifndef PTR_STACK
#define PTR_STACK

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top, length;
    void **data;
} ptr_stack;

void init_ptr_stack(ptr_stack *S, int length) {
    S->length = length;
    S->top = -1;
    S->data = malloc(sizeof(void *) * length);
}

ptr_stack *create_ptr_stack(int n) {
    ptr_stack *s = (ptr_stack *) malloc(sizeof(ptr_stack));
    init_ptr_stack(s, n);
    return s;
}

int ptr_stack_empty(ptr_stack *S) {
    return S->top == -1;
}

void ptr_stack_push(ptr_stack *S, void *x) {
    S->data[++S->top] = x;
}

void *ptr_stack_pop(ptr_stack *S) {
    if (ptr_stack_empty(S))
        fprintf(stderr, "underflow");
    else {
        return S->data[S->top--];
    }
    return 0;
}

#endif