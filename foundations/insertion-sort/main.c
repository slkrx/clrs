#include "../argtoarr.c"
#include <stdio.h>

int main(int argc, char **argv)
{
    int *A, len, i, j, key;

    len = argc - 1;
    A = argtoarr(argc, argv);

    for (j = 1; j < len; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] < key) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }

    for (i = 0; i < len; i++)
        printf("%d%c", A[i], i == len - 1 ? '\n' : ' ');

    return 0;
}