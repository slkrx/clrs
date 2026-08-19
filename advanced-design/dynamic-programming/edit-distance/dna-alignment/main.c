#include <stdlib.h>
#include <stdio.h>
#include "ed.c"

int main() {
    float *cost;
    solution *s;
    int n, m, i, j;
    char *x = "GATCGGCAT";
    char *y = "CAATGTGAATC";

    cost = (float*) malloc(sizeof(float) * 6);
    cost[COPY] = -1;
    cost[REPLACE] = 1;
    cost[DELETE] = 2;
    cost[INSERT] = 2;
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
    printf("%0.2f\n", s->min_cost);
    print_solution(s->ops, s->min_pair, m, n);
}