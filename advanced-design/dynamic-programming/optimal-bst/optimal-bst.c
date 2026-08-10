#include <limits.h>
#include <stdlib.h>
#include "bst.c"

typedef struct {
    float **e;
    int **root;
} solution;

solution *optimal_bst (float *p, float *q, int n) {
    float **e, **w, t;
    int **root, i, l, j, r;
    solution *s;

    s = (solution *) malloc(sizeof(solution));
    e = (float **) malloc(sizeof(float*) * (n+2));
    w = (float **) malloc(sizeof(float *) * (n+2));
    root = (int **) malloc(sizeof(int*) * (n+1));

    for (i = 1; i <= n + 1; i++) {
        e[i] = (float *) malloc(sizeof(float) * (n+1));
        w[i] = (float *) malloc(sizeof(float) * (n+1));
        root[i] = (int *) malloc(sizeof(int) * (n+1));
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }
    for (l = 1; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            // for (r = i; r <= j; r++) {
            //     t = e[i][r-1] + e[r+1][j] + w[i][j];
            //     if (t < e[i][j]) {
            //         e[i][j] = t;
            //         root[i][j] = r;
            //     }
            // }
            if (i == j) {
                root[i][j] = i;
                e[i][j] = e[i][j-1] + e[i+1][j] + w[i][j];
            }
            else 
                for (r = root[i][j-1]; r <= root[i+1][j]; r++) {
                    t = e[i][r-1] + e[r+1][j] + w[i][j];
                    if (t < e[i][j]) {
                        e[i][j] = t;
                        root[i][j] = r;
                    }
                }
        }
    }
    s->e = e;
    s->root = root;
    return s;
}

node *_construct_opt_tree(bst * T, int **root, int i, int j) {
    node *n;
    char *key;
    int r;

    if (i > j)
        return create_node(T, itok(i - 1, 'd'));

    r = root[i][j];
    n = create_node(T, itok(r, 'k'));
    n->left = _construct_opt_tree(T, root, i, r - 1);
    n->right = _construct_opt_tree(T, root, r + 1, j);
    n->height = n->left->height > n->right->height ? n->left->height + 1 : n->right->height + 1;
    return n;
} 

bst *construct_opt_tree(int **root, int n) {
    bst *T = create_tree();
    T->root = _construct_opt_tree(T, root, 1, n);
    return T;
}