#include <stdlib.h>
#include <stdio.h>

#define MAX(X, Y) ((X) >= (Y) ? (X) : (Y))

void longest_palindrome(char **t, int **r, char *s, int n) {
    int l, i, j;

    for (i = 0; i < n; i++) {
        r[i][i] = 1;
        t[i][i] = '/';
    }

    for (l = 1; l <= n; l++)
        for (i = 0; i < n - l; i++) {
            j = i + l;
            if (s[i] == s[j]) {
                r[i][j] = r[i+1][j-1] + 2;
                t[i][j] = '/';
            }
            else if (r[i+1][j] >= r[i][j-1]) {
                r[i][j] = r[i+1][j];
                t[i][j] = '|';
            }
            else {
                r[i][j] = r[i][j-1];
                t[i][j] = '-';
            }
        }
}

void print_solution(int **r, char **t, int n, char *s) {
    int m, i, j, k;
    char *sol;

    m = r[0][n-1];
    sol = (char*) malloc(sizeof(char) * m + 1);
    sol[m] = '\0';
    k = i = 0;
    j = n - 1;
    while (i <= j) {
        if (t[i][j] == '/') {
            sol[k] = sol[m-1-k] = s[i];
            k++;
            i++;
            j--;
        } else if (t[i][j] == '|')
            i++;
        else
            j--;
    }
    printf("%s\n", sol);
}