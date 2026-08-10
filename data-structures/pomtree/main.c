#include "pomtree.c"

int main() {
    ostree *T = create_tree();
    insert(T, 17, 1);
    insert(T, 8, 1);
    insert(T, 25, 1);
    insert(T, 5, 1);
    insert(T, 15, 1);
    insert(T, 1, 1);
    insert(T, 6, 1);
    insert(T, 16, 1);
    insert(T, 19, 1);
    insert(T, 26, 1);
    insert(T, 20, -1);
    insert(T, 23, -1);
    insert(T, 26, -1);
    insert(T, 30, -1);
    insert(T, 9, -1);
    insert(T, 19, -1);
    insert(T, 21, -1);
    insert(T, 3, -1);
    insert(T, 8, -1);
    insert(T, 10, -1);
    printf("%d\n", T->root->o->key);
    print_tree_visual(T);
}