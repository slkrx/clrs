#include <stdio.h>
#include "../argtoarr.c"

void swap(int *, int *);

int main(int argc, char **argv)
{
    int *A, min, n, i, j;

    A = argtoarr(argc, argv);
    n = argc - 1;
    min = 0;
    
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i; j < n; j++)
            if (A[j] < A[min])
                min = j;
        swap(A + i, A + min);
    }

    for (i = 0; i < n; i++)
        printf("%d%c", A[i], i == n - 1 ? '\n' : ' ');
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}