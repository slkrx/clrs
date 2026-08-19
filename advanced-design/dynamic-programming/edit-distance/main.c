#include <stdlib.h>
#include <stdio.h>
#include "ed.c"

int main() {
    // char *x = "algorithm", *y = "altruistic";
    // char *x = "einstein", *y = "rechsteiner";
    char *x = "alphabet", *y = "apple";
    float *cost;
    solution *s;
    int n, m, i, j;

    cost = (float*) malloc(sizeof(float) * 6);
    cost[COPY] = 2;
    cost[REPLACE] = 3.5;
    cost[DELETE] = 1;
    cost[INSERT] = 3;
    cost[TWIDDLE] = 2.5;
    cost[KILL] = 1;
    n = m = 0;
    for (i = 0; x[i] != '\0'; i++)
        m++;
    for (i = 0; y[i] != '\0'; i++)
        n++;

    s = edit_distance(x, y, cost);

    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            printf("%7s%c", op_to_s(s->ops[i][j]), j == n ? '\n' : ' ');
    for (i = 0; i <= m; i++)
        for (j = 0; j <= n; j++)
            printf("%0.2f%c", s->c[i][j], j == n ? '\n' : ' ');
    printf("i: %d, j: %d\n", s->min_pair.i, s->min_pair.j);
    print_solution(s->ops, s->min_pair, m, n);
}
// int main() {
    // char *x = "algorithm", *y = "altruistic", *z, **o;
    // int i, j, n, m;
    // float *cost, **c;

    // n = m = 0;
    // for (i = 0; x[i] != '\0'; i++)
    //     m++;
    // for (i = 0; y[i] != '\0'; i++)
    //     n++;

    // o = (char**) malloc(sizeof(char*) * m);
    // c = (float**) malloc(sizeof(float*) * m);
    // for (i = 0; i < m; i++) {
    //     o[i] = (char*) malloc(sizeof(char) * n);
    //     c[i] = (float*) malloc(sizeof(float) * n);
    // }
    // z = (char*) malloc(sizeof(char) * (n + 1));
    // cost = (float*) malloc(sizeof(float) * 6);
    // cost[COPY] = 2;
    // cost[REPLACE] = 3.5;
    // cost[DELETE] = 1;
    // cost[INSERT] = 3;
    // cost[TWIDDLE] = 2.5;
    // cost[KILL] = 1;
    // printf("%0.2f\n", edit_distance_recursive(x, y, m - 1, n - 1, m, n, cost, o, c));
    // for (i = 0; i < m; i++)
    //     for (j = 0; j < n; j++)
    //         printf("%c%c", o[i][j], j == n - 1 ? '\n' : ' ');
    // for (i = 0; i < m; i++)
    //     for (j = 0; j < n; j++)
    //         printf("%0.2f%c", c[i][j], j == n - 1 ? '\n' : ' ');
    // float min = __FLT_MAX__;
    // int min_i;
    // for (i = 0; i < m; i++)
    //     if (c[i][n-1] < min) {
    //         min = c[i][n-1];
    //         min_i = i;
    //     }
    // i = min_i;
    // printf("%d\n", min_i);
    // j = n - 1;
    // char op;
    // while(i >= 0 && j >= 0) {
    //     op = o[i][j];
    //     printf("%c ", op);
    //     switch (op) {
    //         case 't':
    //             i -= 2; j -= 2; break;
    //         case 'c':
    //             i--; j--; break;
    //         case 'i':
    //             j--; break;
    //         case 'd':
    //             i--; break;
    //         case 'r':
    //             i--; j--; break;
    //     }
    // }
// }