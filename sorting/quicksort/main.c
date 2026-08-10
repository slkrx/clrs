#include <stdio.h>
#include "../argtoarr.c"
#include <stdlib.h>
#include <time.h>

#define k 30

void swap(int *p, int *q) {
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

int partition(int *A, int p, int r) {
    int x, i, j, z;

    z = rand() % (r - p + 1) + p;
    swap(A + r, A + z);

    x = A[r];
    i = p - 1;
    for (j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A + i, A + j);
        }
    }
    swap(A + i + 1, A + r);
    return i + 1;
}

void insertionsort(int *A, int n) {
    int i, j, key;

    for (j = 1; j < n; j++) {
        key = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = key;
    }
}

void _quicksort(int *A, int p, int r) {
    int q;

    if (r - p + 1 > k) {
        q = partition(A, p, r);
        _quicksort(A, p, q - 1);
        _quicksort(A, q + 1, r);
    }
}

void quicksort(int *A, int n) {
    _quicksort(A, 0, n - 1);
    insertionsort(A, n);
}

int hoare_partition(int *A, int p, int r) {
    int x, i, j;

    x = A[p];
    i = p - 1;
    j = r + 1;
    while (1) {
        do {
            j--;
        } while (A[j] > x);
        do {
            i++;
        } while (A[i] < x);
        if (i < j)
            swap(A + i, A + j);
        else
            return j;
    }
}

void _hoare_quicksort(int *A, int p, int r) {
    int q;

    if (p < r) {
        q = hoare_partition(A, p, r);
        if (q == p) {
            if (p + 1 < r) {
                _hoare_quicksort(A, p + 1, r);
            }
        } else {
            _hoare_quicksort(A, p, q);
            _hoare_quicksort(A, q, r);
        }
    }
}

void hoare_quicksort(int *A, int n) {
    _hoare_quicksort(A, 0, n - 1);
}

void printa(int *A, int i, int j, int r) {
    int x = 0;
    if (i >= 0) {
        for (; x < i; x++) 
            printf("    ");
        printf("  i ");
        x++;
    }
    for (; x < j; x++)
        printf("    ");
    printf("  j ");
    x++;
    for (; x < r; x++)
        printf("    ");
    printf("  r \n");
    for (x = 0; x < 20; x++)
        printf("%3d%c", A[x], x == 19 ? '\n' : ' ');
}


struct pair {
    int q, t;
};

struct pair equal_partition(int *A, int p, int r) {
    int x, i, j, k_, q, t;

    x = A[r];
    i = p - 1;
    k_ = r;
    j = p;

    while (j < k_) {
        // printa(A, i, j, k_);
        if (A[j] < x) {
            i++;
            swap(A + i, A + j);
            j++;
        } else if (A[j] > x) {
            j++;
        } else {
            k_--;
            swap(A + j, A + k_);
        }
    }
    q = t = i + 1;
    while (k_ <= r) {
        swap(A + t, A + k_);
        k_++;
        t++;
    }
    t--;
    return (struct pair) { q, t };
}

void _equal_quicksort(int *A, int p, int r) {
    int q, t;
    struct pair u;

    if (p < r) {
        u = equal_partition(A, p, r);
        _equal_quicksort(A, p, u.q - 1);
        _equal_quicksort(A, u.t + 1, r);
    }
}

void equal_quicksort(int *A, int n) {
    _equal_quicksort(A, 0, n - 1);
}

int main(int argc, char **argv) {
    int n = 100, *A;
    // struct timespec start, stop;
    // double elapsed_time;

    A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        // A[i] = rand();
        A[i] = rand() % 50;
    }

    // clock_gettime(CLOCK_MONOTONIC, &start);
    // quicksort(A, n);
    // clock_gettime(CLOCK_MONOTONIC, &stop);
    // elapsed_time = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_nsec - start.tv_nsec) / 1000000.0;
    // printf("%g\n", elapsed_time);

    // printf("%d\n", A[0]);
    // printf("%d\n", A[n-1]);

    // int A[] = { 27,17,3,16,13,10,1,5,7,12,4,8,9,0,22,54,33,67,99,42 };
    // int n = 20;
    // hoare_quicksort(A, n);
    // for (int i = 0; i < n; i++)
    //     printf("%d%c", A[i], i == n - 1 ? '\n' : ' ');

    // int A[] = { 27,17,3,16,13,10,1,5,7,12,4,8,9,0,22,54,33,13,13,13 };
    // int n = 20;
    equal_quicksort(A, n);
    for (int i = 0; i < n; i++)
        printf("%d%c", A[i], i == n - 1 ? '\n' : ' ');
}