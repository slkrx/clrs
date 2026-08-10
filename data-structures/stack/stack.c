#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top, length, *data;
} stack;

stack *create_stack(int n) {
    stack *s = (stack *) malloc(sizeof(stack));
    init_stack(s, n);
    return s;
}

void init_stack(stack *S, int length) {
    S->length = length;
    S->top = -1;
    S->data = malloc(sizeof(int) * length);
}

int stack_empty(stack *S) {
    return S->top == -1;
}

void stack_push(stack *S, int x) {
    S->data[++S->top] = x;
}

int stack_pop(stack *S) {
    if (stack_empty(S))
        fprintf(stderr, "underflow");
    else {
        return S->data[S->top--];
    }
    return 0;
}