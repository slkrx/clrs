#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "../argtoarr.c"

void merge(int *, int, int, int);
void merge_sort(int *, int, int);
int inv = 0;

int main(int argc, char **argv)
{
    int *A, n, i, j, real_inv;
    
    real_inv = 0;
    A = argtoarr(argc, argv);
    n = argc - 1;

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (A[i] > A[j])
                real_inv++;

    merge_sort(A, 0, n - 1);

    printf("%d\n", inv);
    printf("%d\n", real_inv);
}

void merge_sort(int *A, int p, int r)
{
    int q;

    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void merge(int *A, int p, int q, int r)
{
    int n1, n2, *L, *R, i, j, k, x;

    x = 0;
    n1 = q - p + 1;
    n2 = r - q;

    L = (int *) malloc(sizeof(int) * n1);
    R = (int *) malloc(sizeof(int) * n2);

    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    for (i = j = 0, k = p; k <= r; k++)
        if (j >= n2 || i < n1 && L[i] <= R[j]) {
            A[k] = L[i++];
            inv += x;
        } else {
            A[k] = R[j++];
            x += 1;
        }
}