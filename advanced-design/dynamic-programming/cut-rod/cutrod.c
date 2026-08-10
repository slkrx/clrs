#include <limits.h>
#include <stdio.h>

void bottom_up_cut_rod(int *p, int n, int *r, int *s) {
    int i, j, q;

    r[0] = 0;
    for (j = 1; j <= n; j++) {
        q = INT_MIN;
        for (i = 1; i <= j; i++) {
            if (q < p[i] + r[j - i]) {
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
}

void print_rod_cut_solution(int *p, int n, int *r, int *s) {
    bottom_up_cut_rod(p, n, r, s);
    while (n > 0) {
        printf("%d ", s[n]);
        n -= s[n];
    }
}

void bottom_up_cut_rod_cost(int *p, int n, int *r, int *s, int c) {
    int i, j, q;

    r[0] = 0;
    for (j = 1; j <= n; j++) {
        q = INT_MIN;
        for (i = 1; i <= j; i++) {
            if (q < p[i] + r[j - i] - c) {
                q = p[i] + r[j - i] - c;
                s[j] = i;
            }
        }
        r[j] = q;
    }
}

void print_rod_cut_solution_cost(int *p, int n, int *r, int *s, int c) {
    bottom_up_cut_rod_cost(p, n, r, s, c);
    while (n > 0) {
        printf("%d ", s[n]);
        n -= s[n];
    }
}

int memoized_cut_rod_aux(int *p, int n, int *r, int *s) {
    int q, i, t, v;

    if (r[n] >= 0)
        return r[n];
    if (n == 0) q = 0;
    else q = INT_MIN;
    for (i = 1; i <= n; i++) {
        t = memoized_cut_rod_aux(p, n - i, r, s);
        if (q < p[i] + t) {
            q = p[i] + t;
            v = i;
        }
    }
    r[n] = q;
    s[n] = v;
    return q;
}

int memoized_cut_rod(int *p, int n, int *r, int *s) {
    int i;

    for (i = 0; i <= n; i++)
        r[i] = INT_MIN;
    return memoized_cut_rod_aux(p, n, r, s);
}

void print_memoized_rod_cut_solution(int *p, int n, int *r, int *s) {
    memoized_cut_rod(p, n, r, s);
    while (n > 0) {
        printf("%d ", s[n]);
        n -= s[n];
    }
}