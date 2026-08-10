#include "../argtoarr.c"
#include <stdio.h>

int binsearch(int *A, int p, int r, int v);

int main(int argc, char **argv)
{
    int *A, n, f;

    A = argtoarr(argc, argv);
    n = argc - 1;

    f = binsearch(A, 0, n - 1, 5);
    printf("%d\n", f);
}

int binsearch(int *A, int p, int r, int v)
{
    if (p > r)
        return -1;
    
    int q;
    q = (p + r) / 2;

    if (A[q] > v)
        return binsearch(A, p, q - 1, v);
    else if (A[q] < v)
        return binsearch(A, q + 1, r, v);
    else
        return q;
}