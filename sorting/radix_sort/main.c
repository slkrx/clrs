#include "../argtoarr.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ith_digit(int a, int i) {
    return (a / (int) pow(10, i)) % 10;
}

int *modified_count_sort(int *A, int n, int d) {
    int *B, *C, i, j;
    B = (int *) malloc(n * sizeof(int));
    C = (int *) malloc(10 * sizeof(int));
    for (i = 0; i < 10; i++)
        C[i] = 0;
    for (j = 0; j < n; j++)
        C[ith_digit(A[j], d)]++;
    for (i = 1; i < 10; i++)
        C[i] = C[i] + C[i - 1];
    for (j = n - 1; j >= 0; j--) {
        C[ith_digit(A[j], d)]--;
        B[C[ith_digit(A[j], d)]] = A[j];
    }
    return B;
}

int *radix_sort(int *A, int n, int d) {
    int i;
    for (i = 0; i < d; i++) {
        int *B = modified_count_sort(A, n, i);
        free(A);
        A = B;
    }
    return A;
}

int main(int argc, char **argv) {
    int *A, *B, n;
    n = argc - 1;
    A = argtoarr(argc, argv);
    B = radix_sort(A, n, 5);
    printarr(B, n);
}