#include <stdlib.h>
#include "../argtoarr.c"
#include <stdio.h>

void count_sort(int *A, int n, int k) {
    int *B, *C, i, j, a;
    C = (int *) malloc((k + 1)* sizeof(int));
    for (i = 0; i <= k; i++)
        C[i] = 0;
    for (j = 0; j < n; j++)
        C[A[j]]++;
    for (i = 1; i <= k; i++)
        C[i] = C[i] + C[i - 1];
    for (j = 0; j < n; j++) {
        while (C[A[j]] > j) {
            a = A[j];
            C[a]--;
            A[j] = A[C[a]];
            A[C[a]] = a;
        }
    }
}

int main(int argc, char **argv) {
    int *A, *B, n;

    n = argc - 1;
    A = argtoarr(argc, argv);
    count_sort(A, n, 10);
    printarr(A, n);
}