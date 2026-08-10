#include "cutrod.c"
#include <stdlib.h>

int main(int argc, char **argv) {
    int *r, *s, n, c;

    n = atoi(argv[1]);
    c = atoi(argv[2]);
    int p[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    r = malloc(sizeof(p) + sizeof(int));
    s = malloc(sizeof(p) + sizeof(int));

    print_rod_cut_solution(p, n, r, s);
    putchar('\n');
    printf("%d\n", r[n]);
    putchar('\n');
    free(r);
    free(s);
    r = malloc(sizeof(p) + sizeof(int));
    s = malloc(sizeof(p) + sizeof(int));

    print_rod_cut_solution_cost(p, n, r, s, c);
    putchar('\n');
    printf("%d\n", r[n]);
    putchar('\n');
    free(r);
    free(s);
    r = malloc(sizeof(p) + sizeof(int));
    s = malloc(sizeof(p) + sizeof(int));

    print_memoized_rod_cut_solution(p, n, r, s);
    putchar('\n');
    printf("%d\n", r[n]);
    putchar('\n');
}