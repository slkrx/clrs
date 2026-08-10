#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "../argtoarr.c"

typedef struct tuple {
    int left;
    int right;
    int sum;
} Tuple;

Tuple *find_max_crossing_subarray(int *, int, int, int);
Tuple *find_maximum_subarray(int *, int, int);
Tuple *brute_force(int *, int, int);
Tuple *hybrid(int *, int, int);
Tuple *linear(int *, int, int);

int main(int argc, char **argv)
{
    int *A, n, i;
    Tuple *solution;
    struct timespec start, stop;
    double elapsed_time;

    n = atoi(argv[1]);
    A = (int *) malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        A[i] = (rand() & ~((~0u) << 1) ? -1 : 1) * (rand() % 100 + 1);

    printf("Recursive:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    solution = find_maximum_subarray(A, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    elapsed_time = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("left: %d, right: %d, sum: %d\n",
        solution->left, solution->right, solution->sum);
    printf("time: %g\n", elapsed_time);

    printf("Brute Force:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    solution = brute_force(A, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    elapsed_time = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("left: %d, right: %d, sum: %d\n",
        solution->left, solution->right, solution->sum);
    printf("time: %g\n", elapsed_time);

    printf("Hybrid:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    solution = hybrid(A, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    elapsed_time = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("left: %d, right: %d, sum: %d\n",
        solution->left, solution->right, solution->sum);
    printf("time: %g\n", elapsed_time);

    printf("Linear:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    solution = linear(A, 0, n - 1);
    clock_gettime(CLOCK_MONOTONIC, &stop);
    elapsed_time = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("left: %d, right: %d, sum: %d\n",
        solution->left, solution->right, solution->sum);
    printf("time: %g\n", elapsed_time);

    return 0;
}

Tuple *make_tuple(int left, int right, int sum)
{
    Tuple *t;
    t = (Tuple *) malloc(sizeof(Tuple));
    t->left = left;
    t->right = right;
    t->sum = sum;
    return t;
}

Tuple *linear(int *A, int low, int high)
{
    int j;
    Tuple *B, *C;

    B = make_tuple(low, low, A[low]);
    C = make_tuple(low, low, A[low]);

    for (j = low; j < high; j++) {
        if (C->sum <= 0) {
            free(C);
            C = make_tuple(j+1, j+1, A[j+1]);
            if (A[j+1] > B->sum) {
                free(B);
                B = make_tuple(j+1, j+1, A[j+1]);
            }
        } else if (C->sum + A[j+1] > B->sum) {
            C->right = j + 1;
            C->sum += A[j+1];
            free(B);
            B = make_tuple(C->left, C->right, C->sum);
        } else {
            C->right = j+1;
            C->sum += A[j+1];
        }
    }
    free(C);
    return B;
}

Tuple *brute_force(int *A, int low, int high)
{
    int left, right, max_sum, i, j, sum;
    left = right = -1;
    max_sum = INT_MIN;

    for (i = low; i <= high; i++) {
        sum = 0;
        for (j = i; j <= high; j++) {
            sum += A[j];
            if (sum >= max_sum) {
                max_sum = sum;
                left = i;
                right = j;
            }
        }
    }

    return make_tuple(left, right, max_sum);
}

Tuple *hybrid(int *A, int low, int high)
{
    int mid;
    Tuple *left, *right, *crossing;

    if (high - low <= 100)
        return brute_force(A, low, high);
    else {
        mid = (low + high) / 2;
        left = find_maximum_subarray(A, low, mid);
        right = find_maximum_subarray(A, mid + 1, high);
        crossing = find_max_crossing_subarray(A, low, mid, high);

        if (left->sum >= right->sum && left->sum >= crossing->sum) {
            free(right);
            free(crossing);
            return left;
        } else if (right->sum >= left->sum && right->sum >= crossing->sum) {
            free(left);
            free(crossing);
            return right;
        } else {
            free(left);
            free(right);
            return crossing;
        }
    }
}

Tuple *find_maximum_subarray(int *A, int low, int high)
{
    int mid;
    Tuple *left, *right, *crossing;

    if (low == high)
        return make_tuple(low, high, A[low]);
    else {
        mid = (low + high) / 2;
        left = find_maximum_subarray(A, low, mid);
        right = find_maximum_subarray(A, mid + 1, high);
        crossing = find_max_crossing_subarray(A, low, mid, high);

        if (left->sum >= right->sum && left->sum >= crossing->sum) {
            free(right);
            free(crossing);
            return left;
        } else if (right->sum >= left->sum && right->sum >= crossing->sum) {
            free(left);
            free(crossing);
            return right;
        } else {
            free(left);
            free(right);
            return crossing;
        }
    }
}

Tuple *find_max_crossing_subarray(int *A, int low, int mid, int high)
{
    int left_sum, right_sum, sum, i, max_left, max_right;

    left_sum = right_sum = INT_MIN;
    sum = 0;
    max_left = max_right = -1;

    for (i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }
    sum = 0;
    for (i = mid + 1; i <= high; i++) {
        sum += A[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }
    return make_tuple(max_left, max_right, left_sum + right_sum);
}