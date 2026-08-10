#include <stdio.h>
#include "queue.c"

int main() {
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    init_queue(q, 5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 8);
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
}