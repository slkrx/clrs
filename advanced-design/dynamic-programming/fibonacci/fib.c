int fib(int n) {
    if (n == 0 || n == 1)
        return n;
    
    return fib(n - 1) + fib(n - 2);
}

int fib_memoized_aux(int n, int *F) {
    if (F[n] > -1)
        return F[n];
    
    if (F[n - 1] == -1)
        F[n - 1] = fib_memoized_aux(n - 1, F);
    if (F[n - 2] == -1)
        F[n - 2] = fib_memoized_aux(n - 2, F);
    return F[n - 1] + F[n - 2];
}

int fib_memoized(int n) {
    int *F, i;

    F = malloc(sizeof(int) * (n + 1));
    for (i = 0; i <= n; i++)
        F[i] = -1;
    F[0] = 0;
    F[1] = 1;

    return fib_memoized_aux(n, F);
}

int bottom_up_fib(int n) {
    int *F, i;

    F = malloc(sizeof(int) * n);
    F[0] = 0;
    F[1] = 1;
    for (i = 2; i < n; i++)
        F[i] = F[i - 1] + F[i - 2];
    return F[n - 1] + F[n - 2];
}