#include <stdlib.h>
#include "bitonic.c"

int main() {
    point p[] = { {0,6}, {1,0}, {2,3}, {5,4}, {6,1}, {7,5}, {8,2} };
    int n = 7;
    solution *s = shortest_bitonic_tour(p, n);
    printf("%02f\n", s->b[n-1][n-1]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%02f%c", s->b[i][j], j == n - 1 ? '\n' : ' ');
    putchar('\n');
    putchar('\n');
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            printf("%d%c", s->r[i][j], j == n - 1 ? '\n' : ' ');
}