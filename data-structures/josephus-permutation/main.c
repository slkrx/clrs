#include "../mingaptree/mgtree.c"
#include <stdlib.h>

int main(int argc, char **argv) {
    int n, N, m, i, k, j, *A, p;
    ostree *T;
    node *x, *y;

    n = atoi(argv[1]);
    N = atoi(argv[1]);
    m = atoi(argv[2]);
    T = create_tree();
    A = malloc(sizeof(int) * n);
    p = 0;

    for (i = 1; i <= n; i++)
        insert(T, i);
    
    k = 1;
    while (T->root != T->nil) {
        j = (m - 1 + k) % n;
        if (j == 0) j = n;
        x = select(T, j);
        A[p++] = x->key;
        y = successor(T, x);
        if (y == T->nil) y = tree_minimum(T->root);
        rb_delete(T, x);
        n--;
        k = rank(T, y);
    }

    for (i = 0; i < N; i++)
        printf("%d ", A[i]);
    putchar('\n');
}