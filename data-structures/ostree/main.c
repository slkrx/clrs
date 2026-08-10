#include "ostree.c"

int main() {
    int elts[] = { 26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 21, 28, 38, 7, 12, 14, 20, 35, 39, 3 };
    ostree *t = create_tree();
    int n = sizeof(elts) / sizeof(int);
    for (int i = 0; i < n; i++) {
        insert(t, elts[i]);
    }
    // print_tree_visual(t);
    // printf("%d\n", iterative_select(t, 17)->key);
    // printf("%d\n", rank(t, search(t, 38)));
    // printf("%d\n", recursive_rank(t, 38));
    printf("%d\n", inv);
    int real_inv = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (elts[i] > elts[j])
                real_inv++;
    printf("%d\n", real_inv);
}