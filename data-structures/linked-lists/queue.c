#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include "singly_linked.c"

typedef struct {
    node *tail;
    list *list;
} queue;

queue *create_queue() {
    queue *q = (queue *) malloc(sizeof(queue));
    q->list = create_list();
    q->tail = NULL;
    return q;
}

void enqueue(queue *q, int x) {
    node *n = create_node(x);
    if (q->list->head == NULL)
        q->list->head = n;
    else
        q->tail->next = n;
    q->tail = n;
}

int dequeue(queue *q) {
    if (q->list->head == NULL) {
        fprintf(stderr, "queue underflow\n");
        return 0;
    }

    node *x = q->list->head;
    q->list->head = x->next;
    int key = x->key;
    if (q->list->head == NULL)
        q->tail = NULL;
    free(x);
    return key;
}

#endif