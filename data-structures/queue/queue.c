#include <stdio.h>
#include <stdlib.h>

struct queue {
    int head, tail, size, length, *data;
};

void init_queue(struct queue *Q, int length) {
    Q->length = length;
    Q->data = (int *) malloc(sizeof(int) * length);
    Q->head = -1;
    Q->tail = 0;
    Q->size = 0;
}

int queue_next(struct queue *q, int pos) {
    if (pos == q->length - 1)
        return 0;
    else
        return pos + 1;
}

int queue_prev(struct queue *q, int pos) {
    if (pos == 0)
        return q->length - 1;
    else
        return pos - 1;
}

void enqueue(struct queue *q, int x) {
    if (q->size == q->length) {
        fprintf(stderr, "queue overflow\n");
        return;
    }
    q->data[q->tail] = x;
    q->tail = queue_next(q, q->tail);
    if (q->head == -1)
        q->head = 0;
    q->size++;
}

int dequeue(struct queue *q) {
    if (q->size == 0) {
        fprintf(stderr, "queue underflow\n");
        return 0;
    }

    int x = q->data[q->head];
    q->head = queue_next(q, q->head);
    q->size--;
    return x;
}