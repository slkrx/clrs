#include "stack.c"

int main(int argc, char **argv) {
    struct stack *s;
    init_stack(s, 10);
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_push(s, 4);
    stack_push(s, 5);
    stack_push(s, 6);
    while(!stack_empty(s))
        printf("%d ", stack_pop(s));
}