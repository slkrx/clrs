#include "lcs.c"

int main() {
    char *X, *Y;
    solution sol;
    int m, n, i, j;

    X = "ABCBDAB";
    Y = "BDCABA";
    sol = lcs_length_memoized(X, Y);
    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    for (i = 0; i < m + 1; i++) {
        for (j = 0; j < n + 1; j++) {
            printf("%c ", sol.b[i][j]);
        }
        putchar('\n');
    }
    print_lcs(sol.b, X, Y);
    print_lcs_no_b(sol.c, X, Y);
    sol = lcs_length(X, Y);
    for (m = 0; X[m] != '\0'; m++);
    for (n = 0; Y[n] != '\0'; n++);
    for (i = 0; i < m + 1; i++) {
        for (j = 0; j < n + 1; j++) {
            printf("%c ", sol.b[i][j]);
        }
        putchar('\n');
    }
    print_lcs(sol.b, X, Y);
    printf("%d\n", lcs_length_no_c(Y, X));
    printf("%d\n", lcs_length_no_c_prelim(Y, X));
    int nums[] = { 37, 50, 96, 61, 5, 31, 73, 49, 87, 66, 54, 10, 98, 26, 76, 16, 61, 45, 23, 66 };
    sol = lcis_length(nums, 20);
    print_lcis(sol.b, nums, 20);
}