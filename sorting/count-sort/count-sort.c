#include <stdlib.h>

int *count_sort(int *A, int n, int k) {
    int *B, *C, i, j;
    B = (int *) malloc(n * sizeof(int));
    C = (int *) malloc((k + 1)* sizeof(int));
    for (i = 0; i <= k; i++)
        C[i] = 0;
    for (j = 0; j < n; j++)
        C[A[j]]++;
    for (i = 1; i <= k; i++)
        C[i] = C[i] + C[i - 1];
    for (j = n - 1; j >= 0; j--) {
        C[A[j]]--;
        B[C[A[j]]] = A[j];
    }
    return B;
}