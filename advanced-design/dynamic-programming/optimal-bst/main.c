#include "optimal-bst.c"
#include <stdio.h>

int main() {
    float p[] = { 0.0, 0.04, 0.06, 0.08, 0.02, 0.1, 0.12, 0.14 };
    float q[] = { 0.06, 0.06, 0.06, 0.06, 0.05, 0.05, 0.05, 0.05};
    int n = 7;
    solution *s = optimal_bst(p, q, n);
    for (int i = 1; i <= n + 1; i++)
        for (int j = 0; j <= n; j++)
            printf("%0.2f%c", s->e[i][j], j == n ? '\n' : ' ');
    putchar('\n');
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            printf("%d%c", s->root[i][j], j == n ? '\n' : ' ');
    putchar('\n');
    bst *t = construct_opt_tree(s->root, n);
    print_tree_visual(t);
}