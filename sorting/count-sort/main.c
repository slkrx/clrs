#include "count-sort.c"
#include "../argtoarr.c"
#include <stdio.h>

int main(int argc, char **argv) {
    int *A, *B, n;

    n = argc - 1;
    A = argtoarr(argc, argv);
    B = count_sort(A, n, 100);
    printarr(B, n);
}