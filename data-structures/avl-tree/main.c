#include "avl-tree.c"

int main() {
    avltree *t = create_tree();
    insert(t, create_node(1));
    insert(t, create_node(2));
    insert(t, create_node(3));
    insert(t, create_node(4));
    insert(t, create_node(5));
    insert(t, create_node(6));
    insert(t, create_node(7));
    insert(t, create_node(8));
    insert(t, create_node(9));
    insert(t, create_node(10));
    insert(t, create_node(11));
    insert(t, create_node(12));
    insert(t, create_node(13));
    insert(t, create_node(14));
    insert(t, create_node(15));
    insert(t, create_node(16));
    insert(t, create_node(17));
    insert(t, create_node(18));
    print_tree_visual(t);
}