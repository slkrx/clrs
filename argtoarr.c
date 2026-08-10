#include <stdlib.h>
#include <stdio.h>

int *argtoarr(int, char**);

int *argtoarr(int argc, char **argv)
{
    int *arr, *p;

    p = arr = (int *) malloc(sizeof(int) * (argc - 1));
    
    while (--argc > 0)
        *p++ = atoi(*++argv);
    
    return arr;
}

void printarr(int *A, int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d%c", A[i], i == n - 1 ? '\n' : ' ');
}