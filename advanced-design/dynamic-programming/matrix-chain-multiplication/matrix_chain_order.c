#ifndef MATRIX_CHAIN_ORDER
#define MATRIX_CHAIN_ORDER

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "matrix.c"

typedef struct {
    int **s, **m;
} response;

response *matrix_chain_order(int *p, int n) {
    int i, j, k, l, q, **m, **s;
    response *res;

    res = (response *) malloc(sizeof(response));
    m = (int**) malloc(sizeof(int*) * n);
    s = (int**) malloc(sizeof(int*) * n);
    for (i = 0; i < n; i++) {
        m[i] = (int*) malloc(sizeof(int) * n);
        m[i][i] = 0;
        s[i] = (int*) malloc(sizeof(int) * n);
    }

    for (l = 2; l <= n; l++) {
        for (i = 0; i <= n - l; i++) {
            j = i + l - 1;
            m[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    res->m = m;
    res->s = s;
    return res;
}

void print_optimal_parens(int **s, int i, int j) {
    setlocale(LC_ALL, "");
    wchar_t subscript = 8320;
    if (i == j)
        printf("A%lc", subscript + i + 1);
    else {
        putchar('(');
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        putchar(')');
    }
}

matrix *matrix_chain_multiply(int **s, int i, int j, matrix **matrices) {
    if (i == j)
        return matrices[i];
    else {
        return matrix_multiply(
            matrix_chain_multiply(s, i, s[i][j], matrices),
            matrix_chain_multiply(s, s[i][j] + 1, j, matrices)
        );
    }
}

#endif