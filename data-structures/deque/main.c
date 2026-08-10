#include <stdio.h>
#include "deque.c"

int main() {
    struct deque *q = (struct deque *) malloc(sizeof(struct deque));
    init_deque(q, 5);
    push_front(q, 1);
    push_front(q, 2);
    push_back(q, 3);
    push_back(q, 4);
    push_back(q, 5);
    for (int i = 0; i < 5; i++)
        printf("%d ", q->data[i]);
    printf("\n");
    push_back(q, 6);
    push_front(q, 7);
    printf("%d\n", pop_back(q));
    printf("%d\n", pop_back(q));
    printf("%d\n", pop_back(q));
    printf("%d\n", pop_front(q));
    printf("%d\n", pop_front(q));
    printf("%d\n", pop_front(q));
}