#include <stdio.h>
#include <stdlib.h>
#include "fib.c"
#include <time.h>

int main(int argc, char **argv) {
    int n;
    clock_t start, end;

    n = atoi(argv[1]);

    // start = clock();
    // printf("%d\n", fib(n));
    // end = clock();
    // printf("%.2f\n", (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    printf("%d\n", fib_memoized(n));
    end = clock();
    printf("%.2f\n", (double) (end - start) / CLOCKS_PER_SEC);

    start = clock();
    printf("%d\n", bottom_up_fib(n));
    end = clock();
    printf("%.2f\n", (double) (end - start) / CLOCKS_PER_SEC);
}