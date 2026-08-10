#include "singly_linked_circular.c"

int main() {
    list *L = create_list();

    list_insert(L, create_node(1));
    list_insert(L, create_node(2));
    list_insert(L, create_node(3));
    list_insert(L, create_node(4));
    print_list(L);
    node* x = list_search(L, 3);
    list_delete(L, x);
    print_list(L);
    list_delete(L, list_search(L, 4));
    print_list(L);
}