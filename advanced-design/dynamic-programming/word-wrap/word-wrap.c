#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct {
    int *b, *c;
} solution;

solution word_wrap(int n, int *L, int M) {
    int extras[n][n], lc[n][n], i, j, k, sum, *c, min, *b;

    c = (int*) malloc(sizeof(int) * n);
    b = (int*) malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sum = 0;
            for (k = i; k <= j; k++)
                sum += L[k];
            extras[i][j] = M - j + i - sum;
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (extras[i][j] < 0)
                lc[i][j] = INT_MAX;
            else if (j == n - 1)
                lc[i][j] = 0;
            else
                lc[i][j] = pow(extras[i][j], 3);
        }
    }

    for (j = 0; j < n; j++) {
        if (lc[0][j] < INT_MAX) {
            c[j] = lc[0][j];
            b[j] = 0;
        } else {
            min = INT_MAX;
            for (k = 0; k <= j; k++) {
                if (lc[k][j] < INT_MAX && c[k-1] + lc[k][j] < min) {
                    min = c[k-1] + lc[k][j];
                    b[j] = k;
                }
            }
            c[j] = min;
        }
    }

    solution s = {b,c};

    return s;
}

int print_solution_(char **words, int *b, int j) {
    int i, k;
    if (b[j] == 0)
        i = 0;
    else 
        i = print_solution_(words, b, b[j] - 1);
    for (k = i; k <= j; k++)
        printf("%s ", words[k]);
    putchar('\n');
    return k;
}

void print_solution(char **words, int *b, int n) {
    print_solution_(words, b, n-1);
}