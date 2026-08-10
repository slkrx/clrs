#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int **c;
    char **b;
} solution;

solution lcs_length(char *X, char *Y) {
    int i, j, m, n, **c;
    char **b;
    solution sol;

    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    c = (int**) malloc(sizeof(int*) * (m + 1));
    b = (char**) malloc(sizeof(char*) * (m + 1));
    for (i = 0; i < m + 1; i++) {
        c[i] = (int*) malloc(sizeof(int) * (n + 1));
        b[i] = (char*) malloc(sizeof(char) * (n + 1));
    }
    for (i = 1; i < m + 1; i++) {
        c[i][0] = 0;
        b[i][0] = ' ';
    }
    for (j = 0; j < n + 1; j++) {
        c[0][j] = 0;
        b[0][j] = ' ';
    }
    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = '\\';
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = '|';
            }
            else {
                c[i][j] = c[i][j-1];
                b[i][j] = '-';
            }
        }
    }
    sol.c = c;
    sol.b = b;
    return sol;
}

solution lcis_length(int *X, int n) {
    int i, j, **c, *Y, temp;
    char **b;
    solution sol;

    c = (int**) malloc(sizeof(int*) * (n + 1));
    b = (char**) malloc(sizeof(char*) * (n + 1));
    Y = (int*) malloc(sizeof(int) * n);
    for (i = 0; i < n + 1; i++) {
        c[i] = (int*) malloc(sizeof(int) * (n + 1));
        b[i] = (char*) malloc(sizeof(char) * (n + 1));
    }
    for (i = 1; i < n + 1; i++) {
        c[i][0] = 0;
        b[i][0] = ' ';
    }
    for (j = 0; j < n + 1; j++) {
        c[0][j] = 0;
        b[0][j] = ' ';
    }
    for (i = 0; i < n; i++)
        Y[i] = X[i];
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j >= 0; j--)
            if (Y[j] < Y[j-1]) {
                temp = Y[j-1];
                Y[j-1] = Y[j];
                Y[j] = temp;
            } else
                continue;
    for (i = 1; i < n + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = '\\';
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = '|';
            }
            else {
                c[i][j] = c[i][j-1];
                b[i][j] = '-';
            }
        }
    }
    sol.c = c;
    sol.b = b;
    return sol;
}

void _print_lcs(char **b, char *X, int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == '\\') {
        _print_lcs(b, X, i-1, j-1);
        printf("%c", X[i-1]);
    }
    else if (b[i][j] == '|')
        _print_lcs(b, X, i-1, j);
    else
        _print_lcs(b, X, i, j-1);
}

void print_lcs(char **b, char *X, char *Y) {
    int m, n;
    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    _print_lcs(b, X, m, n);
    putchar('\n');
}

void _print_lcis(char **b, int *X, int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == '\\') {
        _print_lcis(b, X, i-1, j-1);
        printf("%d ", X[i-1]);
    }
    else if (b[i][j] == '|')
        _print_lcis(b, X, i-1, j);
    else
        _print_lcis(b, X, i, j-1);
}

void print_lcis(char **b, int *X, int n) {
    _print_lcis(b, X, n, n);
    putchar('\n');
}

void _print_lcs_no_b(int **c, char *X, char *Y, int i, int j) {
    if (i == 0 || j == 0)
        return;
    if (X[i-1] == Y[j-1]) {
        _print_lcs_no_b(c, X, Y, i-1, j-1);
        printf("%c", X[i-1]);
    }
    else if (c[i-1][j] >= c[i][j-1])
        _print_lcs_no_b(c, X, Y, i-1, j);
    else
        _print_lcs_no_b(c, X, Y, i, j-1);
}

void print_lcs_no_b(int **c, char *X, char *Y) {
    int m, n;
    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    _print_lcs_no_b(c, X, Y, m, n);
    putchar('\n');
}

void _lcs_length_memoized(char *X, char *Y, int **c, char **b, int i, int j) {
    if (i == 0 || j == 0) {
        c[i][j] = 0;
        b[i][j] = ' ';
    }
    else if (X[i-1] == Y[j-1]) {
        if (c[i-1][j-1] == -1)
            _lcs_length_memoized(X, Y, c, b, i-1, j-1);
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = '\\';
    }
    else {
        if (c[i-1][j] == -1)
            _lcs_length_memoized(X, Y, c, b, i-1, j);
        if (c[i][j-1] == -1)
            _lcs_length_memoized(X, Y, c, b, i, j-1);
        if (c[i-1][j] >= c[i][j-1]) {
            c[i][j] = c[i-1][j];
            b[i][j] = '|';
        }
        else {
            c[i][j] = c[i][j-1];
            b[i][j] = '-';
        }
    }
}

solution lcs_length_memoized(char *X, char *Y) {
    int i, j, m, n, **c;
    char **b;
    solution sol;

    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    c = (int**) malloc(sizeof(int*) * (m + 1));
    b = (char**) malloc(sizeof(char*) * (m + 1));
    for (i = 0; i < m + 1; i++) {
        c[i] = (int*) malloc(sizeof(int) * (n + 1));
        b[i] = (char*) malloc(sizeof(char) * (n + 1));
        for (j = 0; j < n + 1; j++) {
            c[i][j] = -1;
            b[i][j] = ' ';
        }
    }
    _lcs_length_memoized(X, Y, c, b, m, n);
    sol.c = c;
    sol.b = b;
    return sol;
}

int lcs_length_no_c_prelim(char *X, char *Y) {
    int i, j, m, n, *c, *b;

    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    if (m < n) {
        char *temp_c = X;
        X = Y;
        Y = temp_c;
        int temp_i = m;
        m = n;
        n = temp_i;
    }
    c = (int*) malloc(sizeof(int) * (n + 1));
    b = (int*) malloc(sizeof(int) * (n + 1));
    for (j = 0; j < n + 1; j++)
        b[i] = 0;
    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < n + 1; j++)
            if (X[i-1] == Y[j-1])
                c[j] = b[j-1] + 1;
            else if (b[j] >= c[j-1])
                c[j] = b[j];
            else
                c[j] = c[j-1];
        for (j = 1; j < n + 1; j++)
            b[j] = c[j];
    }
    return c[n];
}

int lcs_length_no_c(char *X, char *Y) {
    int i, j, m, n, *c, b, temp;

    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    if (m < n) {
        char *temp_c = X;
        X = Y;
        Y = temp_c;
        int temp_i = m;
        m = n;
        n = temp_i;
    }
    c = (int*) malloc(sizeof(int) * (n + 1));
    c[0] = 0;
    c[1] = 0;
    b = 0;
    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            temp = c[j];
            if (X[i-1] == Y[j-1])
                c[j] = b + 1;
            else if (c[j] < c[j-1])
                c[j] = c[j-1];
            b = temp;
        }
        b = 0;
    }
    return c[n];
}