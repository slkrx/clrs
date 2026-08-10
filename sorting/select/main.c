#include <stdio.h>
#include <stdlib.h>
#include "../argtoarr.c"

void swap(int *p, int *q) {
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

int partition(int *A, int p, int r) {
    int x, i, j, z;

    z = rand() % (r - p + 1) + p;
    swap(A + r, A + z);

    x = A[r];
    i = p - 1;
    for (j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A + i, A + j);
        }
    }
    swap(A + i + 1, A + r);
    return i + 1;
}

int select(int *A, int p, int r, int i) {
    int q, k;

    if (p == r)
        return A[p];
    q = partition(A, p, r);
    k = q - p + 1;
    if (i == k)
        return A[q];
    else if (i < k)
        return select(A, p, q-1, i);
    else 
        return select(A, q+1, r, i-k);
}

int select_iterative(int *A, int p, int r, int i) {
    int q, k;

    while (p <= r) {
        if (p == r)
            return A[p];
        q = partition(A, p, r);
        k = q - p + 1;
        if (i == k)
            return A[q];
        else if (i < k)
            r = q - 1;
        else {
            p = q + 1;
            i -= k;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    int *A, n, k;
    n = argc - 1;
    A = argtoarr(argc, argv);

    k = select_iterative(A, 0, n - 1, 5);
    printf("%d\n", k);
}