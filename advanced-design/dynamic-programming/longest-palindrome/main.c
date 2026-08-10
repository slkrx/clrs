#include <stdio.h>
#include "palindrome.c"
#include <stdlib.h>

int main() {
    int n, **r, i, j;
    char *s, **t;
    
    s = "dfjkslafjioreufjnvcxagruiepwjfdskal";
    for (n = 0; s[n] != '\0'; n++);
    r = (int**) malloc(sizeof(int*) * n);
    t = (char**) malloc(sizeof(char*) * n);
    for (i = 0; i < n; i++) {
        r[i] = (int*) malloc(sizeof(int) * n);
        t[i] = (char*) malloc(sizeof(char) * n);
        for (j = 0; j < n; j++)
            t[i][j] = ' ';
    }

    longest_palindrome(t, r, s, n);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            printf("%d%c", r[i][j], j == n - 1 ? '\n' : ' ');
    putchar('\n');
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            printf("%c%c", t[i][j], j == n - 1 ? '\n' : ' ');
    putchar('\n');
    
    print_solution(r, t, n, s);
}