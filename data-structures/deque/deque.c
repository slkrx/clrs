#include <stdio.h>
#include <stdlib.h>

struct deque {
    int head, tail, size, length, *data;
};

void init_deque(struct deque *Q, int length) {
    Q->length = length;
    Q->data = (int *) malloc(sizeof(int) * length);
    Q->head = 0;
    Q->tail = 0;
    Q->size = 0;
}

int deque_next(struct deque *q, int pos) {
    if (pos == q->length - 1)
        return 0;
    else
        return pos + 1;
}

int deque_prev(struct deque *q, int pos) {
    if (pos == 0)
        return q->length - 1;
    else
        return pos - 1;
}

void push_back(struct deque *q, int x) {
    if (q->size == q->length) {
        fprintf(stderr, "deque overflow\n");
        return;
    }
    q->data[q->tail] = x;
    q->tail = deque_next(q, q->tail);
    q->size++;
}

void push_front(struct deque *q, int x) {
    if (q->size == q->length) {
        fprintf(stderr, "deque overflow\n");
        return;
    }
    q->head = deque_prev(q, q->head);
    q->data[q->head] = x;
    q->size++;
}

int pop_front(struct deque *q) {
    if (q->size == 0) {
        fprintf(stderr, "deque underflow\n");
        return 0;
    }
    int x = q->data[q->head];
    q->head = deque_next(q, q->head);
    q->size--;
    return x;
}

int pop_back(struct deque *q) {
    if (q->size == 0) {
        fprintf(stderr, "deque underflow\n");
        return 0;
    }
    q->tail = deque_prev(q, q->tail);
    int x = q->data[q->tail];
    q->size--;
    return x;
}