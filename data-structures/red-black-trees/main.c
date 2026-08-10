#include "rbt.c"

int main() {
    rbtree *T = create_tree();
    rb_insert_key(T, 41);
    rb_insert_key(T, 38);
    rb_insert_key(T, 31);
    rb_insert_key(T, 12);
    rb_insert_key(T, 19);
    rb_insert_key(T, 8);

    print_tree_preorder(T, T->root);
    putchar('\n');

    rb_delete(T, tree_search(T, T->root, 8));
    print_tree_preorder(T, T->root);
    putchar('\n');
    rb_delete(T, tree_search(T, T->root, 12));
    print_tree_preorder(T, T->root);
    putchar('\n');
    rb_delete(T, tree_search(T, T->root, 19));
    print_tree_preorder(T, T->root);
    putchar('\n');
    rb_delete(T, tree_search(T, T->root, 31));
    print_tree_preorder(T, T->root);
    putchar('\n');
    rb_delete(T, tree_search(T, T->root, 38));
    print_tree_preorder(T, T->root);
    putchar('\n');
    rb_delete(T, tree_search(T, T->root, 41));
    print_tree_preorder(T, T->root);
    putchar('\n');
}