#include "mgtree.c"

int main() {
    int keys[] = { 26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 22, 28, 38, 7, 12, 15, 20, 35, 39, 3 };
    ostree *T = create_tree();
    for (int i = 0; i < sizeof(keys) / sizeof(int); i++)
        insert(T, keys[i]);
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);
    rb_delete(T, search(T, 17));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 19));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 15));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 20));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 21));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 38));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 28));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 14));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 10));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 41));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 26));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 16));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 7));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);

    rb_delete(T, search(T, 39));
    print_tree_visual(T);
    printf("%d\n", T->root->mingap);
    printf("%d,%d\n", search_mingap(T)[0]->key, search_mingap(T)[1]->key);
}