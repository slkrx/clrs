#include "singly_linked.c"
#include "stack.c"
#include "queue.c"

int main() {
    list *L = (list *) malloc(sizeof(list));
    init_list(L);

    list_insert(L, create_node(1));
    list_insert(L, create_node(2));
    list_insert(L, create_node(3));
    list_insert(L, create_node(4));
    print_list(L);
    reverse_list(L);
    print_list(L);
    node* x = list_search(L, 3);
    list_delete(L, x);
    print_list(L);
    list_delete(L, list_search(L, 4));
    print_list(L);

    stack *s = create_stack();
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_push(s, 4);
    stack_push(s, 5);
    stack_push(s, 6);
    while(!stack_empty(s))
        printf("%d ", stack_pop(s));
    printf("\n\n");

    queue *q = create_queue();
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    print_list(q->list);
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
    printf("%d ", dequeue(q));
    printf("%d ", dequeue(q));
}