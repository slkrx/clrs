#include <stdio.h>
#include "doubly_linked.c"

int main() {
    list *l = create_list();
    list_insert(l, create_node(1));
    list_insert(l, create_node(2));
    list_insert(l, create_node(3));
    list_insert(l, create_node(4));
    list_insert(l, create_node(5));
    print_list(l);
    list_delete(l, list_search(l, 5));
    list_delete(l, list_search(l, 1));
    list_delete(l, list_search(l, 4));
    list_delete(l, list_search(l, 2));
    list_delete(l, list_search(l, 3));
    print_list(l);
    list_insert(l, create_node(1));
    list_insert(l, create_node(2));
    list_insert(l, create_node(3));
    list_insert(l, create_node(4));
    list_insert(l, create_node(5));
    print_list(l);
}