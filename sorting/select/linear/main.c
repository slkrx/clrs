#include "../../argtoarr.c"
#include <stdio.h>
#include <math.h>

void insertion_sort(int *A, int p, int q, int n, int depth) {
    int i, key, j;

    for (i = p + pow(5, depth); i < n && i <= q; i = i + pow(5, depth)) {
        key = A[i];
        j = i - pow(5, depth);
        while (j >= p && A[j] > key) {
            A[j + (int) pow(5, depth)] = A[j];
            j = j - pow(5, depth);
        }
        A[j + (int) pow(5, depth)] = key;
    }
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int *A, int p, int r, int s) {
    int x, i, j;

    swap(A + r, A + s);

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

int select(int *A, int p, int q, int i, int n, int depth) {
    int j, k, *B, m, x, l, t, low, high, size, partition_median, x_index;

    for (j = p + pow(5, depth) / 2; j < n && j <= q; j += 5 * pow(5, depth)) {
        insertion_sort(A, j, j + 4 * pow(5, depth), n, depth);
    }
    
    printarr(A, n);

    if (depth == 1)
        return 0;

    x = select(A, p, q, ((int) ((q - p + 1) / pow(5, depth + 1))) / 2, n, depth + 1);

    return 0;

    // t = partition(A, p, q, x);
    // k = t - p + 1;
    // if (i == k)
    //     return x;
    // else if (i < k)
    //     return select(A, p, t - 1, i, n);
    // else
    //     return select(A, t + 1, q, i - k, n);
}

int main(int argc, char **argv) {
    int *A, n;

    A = argtoarr(argc, argv);
    n = argc - 1;

    select(A, 0, n - 1, n / 2, n, 0);
}
