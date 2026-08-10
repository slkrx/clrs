#include "arbtree.c"

int main() {
    int elts[] = { 26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 22, 28, 38, 7, 12, 15, 20, 35, 39, 3 };
    ostree *t = create_tree();
    int n = sizeof(elts) / sizeof(int);
    for (int i = 0; i < n; i++) {
        insert(t, elts[i]);
    }
    // printf("%d\n", tree_minimum(t)->key);
    print_tree_visual(t);
    putchar('\n');
    printf("%d\n", search(t, 26)->bh);
    printf("%d\n", search(t, 41)->bh);
    printf("%d\n", search(t, 38)->bh);
    printf("%d\n", search(t, 35)->bh);
    printf("%d\n", search(t, 47)->predecessor->key);
    printf("%d\n", search(t, 38)->predecessor->key);
    printf("%d\n", search(t, 21)->predecessor->key);
    printf("%d\n", search(t, 26)->successor->key);
    printf("%d\n", search(t, 14)->successor->key);
    printf("%d\n", search(t, 20)->successor->key);
    rb_delete(t, search(t, 47));
    print_tree_visual(t);
    putchar('\n');
    rb_delete(t, search(t, 16));
    print_tree_visual(t);
    putchar('\n');
    rb_delete(t, search(t, 30));
    print_tree_visual(t);
    printf("%d\n", tree_minimum(t->root)->key);
    putchar('\n');
    rb_delete(t, search(t, 3));
    print_tree_visual(t);
    putchar('\n');
    rb_delete(t, search(t, 41));
    print_tree_visual(t);
    putchar('\n');
    printf("%d\n", tree_minimum(t->root)->key);
    printf("%d\n", tree_maximum(t->root)->key);
    printf("%d\n", search(t, 35)->predecessor->key);
    printf("%d\n", search(t, 28)->successor->key);
    printf("%d\n", search(t, 17)->predecessor->key);
    printf("%d\n", search(t, 15)->successor->key);
    printf("%d\n", search(t, 38)->predecessor->key);
    printf("%d\n", search(t, 22)->successor->key);
    printf("%d\n", search(t, 26)->bh);
    printf("%d\n", search(t, 35)->bh);
    rb_delete(t, search(t, 26));
    print_tree_visual(t);
    putchar('\n');
    printf("%d\n", search(t, 28)->bh);
    printf("%d\n", search(t, 21)->bh);
    printf("%d\n", search(t, 17)->bh);
    printf("%d\n", search(t, 14)->bh);
    printf("%d\n", search(t, 35)->bh);
}