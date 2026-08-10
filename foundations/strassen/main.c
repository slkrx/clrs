#include <stdio.h>
#include <stdlib.h>

struct pt
{
    int i, j;
};

struct matrix
{
    struct pt origin;
    int *base, nrow, n;
};

int get(struct matrix A, struct pt p)
{
    int i = A.origin.i + p.i - 1;
    int j = A.origin.j + p.j - 1;
    return A.base[(i-1) * A.nrow + (j-1)];
}

void set(struct matrix A, struct pt p, int z)
{
    int i = A.origin.i + p.i - 1;
    int j = A.origin.j + p.j - 1;
    A.base[(i-1) * A.nrow + (j-1)] = z;
}

void print(struct matrix A)
{
    int i,j;
    for (i = 1; i <= A.n; i++)
        for (j = 1; j <= A.n; j++)
            printf("%5d%c", get(A, (struct pt) {i, j}), j == A.n ? '\n' : ' ');
}

struct matrix copydim(struct matrix A)
{
    struct matrix C;
    C.n = A.n;
    C.nrow = A.n;
    C.origin = (struct pt) {1,1};
    C.base = (int *) malloc(C.n * C.n * sizeof(int));
    return C;
}

struct matrix mem_add(struct matrix A, struct matrix B)
{
    struct matrix C = copydim(A);
    int i, j, z;
    for (i = 1; i <= C.n; i++)
        for (j = 1; j <= C.n; j++) {
            z = get(A, (struct pt) {i, j}) + get(B, (struct pt) {i, j});
            set(C, (struct pt) {i, j}, z);
        }
    return C;
}

struct matrix mem_subtract(struct matrix A, struct matrix B)
{
    struct matrix C = copydim(A);
    int i, j, z;
    for (i = 1; i <= C.n; i++)
        for (j = 1; j <= C.n; j++) {
            z = get(A, (struct pt) {i, j}) - get(B, (struct pt) {i, j});
            set(C, (struct pt) {i, j}, z);
        }
    return C;
}

struct matrix naive_multiply(struct matrix A, struct matrix B)
{
    struct matrix C = copydim(A);
    int i, j, k, sum;
    for (i = 1; i <= C.n; i++)
        for (j = 1; j <= C.n; j++) {
            sum = 0;
            for (k = 1; k <= C.n; k++)
                sum += get(A, (struct pt) {i, k}) * get(B, (struct pt) {k, j});
            set(C, (struct pt) {i, j}, sum);
        }
    return C;
}

void add(struct matrix A, struct matrix B, struct matrix C)
{
    int i, j, z;
    for (i = 1; i <= C.n; i++)
        for (j = 1; j <= C.n; j++) {
            z = get(A, (struct pt) {i, j}) + get(B, (struct pt) {i, j});
            set(C, (struct pt) {i, j}, z);
        }
}

void subtract(struct matrix A, struct matrix B, struct matrix C)
{
    int i, j, z;
    for (i = 1; i <= C.n; i++)
        for (j = 1; j <= C.n; j++) {
            z = get(A, (struct pt) {i, j}) - get(B, (struct pt) {i, j});
            set(C, (struct pt) {i, j}, z);
        }
}

void partition(struct matrix *A, struct matrix *A11, struct matrix *A12, struct matrix *A21, struct matrix *A22)
{
    A11->base = A12->base = A21->base = A22->base = A->base;
    A11->nrow = A12->nrow = A21->nrow = A22->nrow = A->nrow;
    A11->n = A12->n = A21->n = A22->n = A->n / 2;
    A11->origin = (struct pt) {A->origin.i, A->origin.j};
    A12->origin = (struct pt) {A->origin.i, A->origin.j + A->n / 2};
    A21->origin = (struct pt) {A->origin.i + A->n / 2, A->origin.j};
    A22->origin = (struct pt) {A->origin.i + A->n / 2, A->origin.j + A->n / 2};
}

struct matrix recursive_multiply(struct matrix A, struct matrix B)
{
    struct matrix C;
    C.base = (int *) malloc(A.n * A.n * sizeof(int));
    C.n = A.n;
    C.nrow = A.n;
    C.origin = (struct pt) {1,1};

    if (C.n == 1) {
        set(
            C, (struct pt) {1,1},
            get(A, (struct pt) {1,1}) * get(B, (struct pt) {1,1})
        );
    }
    else {
        struct matrix
            C11, C12, C21, C22,
            A11, A12, A21, A22,
            B11, B12, B21, B22,
            S1, S2, S3, S4, S5, S6, S7, S8;
        partition(&A, &A11, &A12, &A21, &A22);
        partition(&B, &B11, &B12, &B21, &B22);
        partition(&C, &C11, &C12, &C21, &C22);
        S1 = recursive_multiply(A11, B11);
        S2 = recursive_multiply(A12, B21);
        add(S1, S2, C11);
        S3 = recursive_multiply(A11, B12);
        S4 = recursive_multiply(A12, B22);
        add(S3, S4, C12);
        S5 = recursive_multiply(A21, B11);
        S6 = recursive_multiply(A22, B21);
        add(S5, S6, C21);
        S7 = recursive_multiply(A21, B12);
        S8 = recursive_multiply(A22, B22);
        add(S7, S8, C22);
        free(S1.base); free(S2.base); free(S3.base); free(S4.base);
        free(S5.base); free(S6.base); free(S7.base); free(S8.base);
    }
    return C;
}

struct matrix strassen_multiply(struct matrix A, struct matrix B)
{
    struct matrix C;
    C.base = (int *) malloc(A.n * A.n * sizeof(int));
    C.n = A.n;
    C.nrow = A.n;
    C.origin = (struct pt) {1,1};

    if (C.n == 1) {
        set(
            C, (struct pt) {1,1},
            get(A, (struct pt) {1,1}) * get(B, (struct pt) {1,1})
        );
    }
    else {
        struct matrix
            A11, A12, A21, A22,
            B11, B12, B21, B22,
            C11, C12, C21, C22,
            S1, S2, S3, S4, S5, S6, S7, S8, S9, S10,
            P1, P2, P3, P4, P5, P6, P7,
            R1, R2, R3, R4;
        partition(&A, &A11, &A12, &A21, &A22);
        partition(&B, &B11, &B12, &B21, &B22);
        partition(&C, &C11, &C12, &C21, &C22);

        S1 = mem_subtract(B12, B22);
        S2 = mem_add(A11, A12);
        S3 = mem_add(A21, A22);
        S4 = mem_subtract(B21, B11);
        S5 = mem_add(A11, A22);
        S6 = mem_add(B11, B22);
        S7 = mem_subtract(A12, A22);
        S8 = mem_add(B21, B22);
        S9 = mem_subtract(A11, A21);
        S10 = mem_add(B11, B12);

        P1 = strassen_multiply(A11, S1);
        P2 = strassen_multiply(S2, B22);
        P3 = strassen_multiply(S3, B11);
        P4 = strassen_multiply(A22, S4);
        P5 = strassen_multiply(S5,S6);
        P6 = strassen_multiply(S7, S8);
        P7 = strassen_multiply(S9, S10);

        R1 = mem_subtract(P4, P2);
        R2 = mem_add(P5, P6);
        add(R1, R2, C11);
        add(P1, P2, C12);
        add(P3, P4, C21);
        R3 = mem_subtract(P5, P3);
        R4 = mem_subtract(P1, P7);
        add(R3, R4, C22);

        free(S1.base); free(S2.base); free(S3.base); free(S4.base);
        free(S5.base); free(S6.base); free(S7.base); free(S8.base);
        free(S9.base); free(S10.base);
        free(P1.base); free(P2.base); free(P3.base); free(P4.base);
        free(P5.base); free(P6.base); free(P7.base);
        free(R1.base); free(R2.base); free(R3.base); free(R4.base);
    }
    return C;
}

int main() {
    struct matrix A;
    A.base = (int[]) {
        1, 2, 3, 4, 1, 2, 3, 4,
        5, 6, 7, 8, 5, 6, 7, 8,
        9, 10, 11, 12, 9, 10, 11, 12,
        13, 14, 15, 16, 13, 14, 15, 16,
        1, 2, 3, 4, 1, 2, 3, 4,
        5, 6, 7, 8, 5, 6, 7, 8,
        9, 10, 11, 12, 9, 10, 11, 12,
        13, 14, 15, 16, 13, 14, 15, 16
    };
    A.origin = (struct pt) {1,1};
    A.nrow = 8;
    A.n = 8;
    print(A);
    printf("\n");

    struct matrix B;
    B.base = (int[]) {
        1, 2, 3, 4, 1, 2, 3, 4,
        5, 6, 7, 8, 5, 6, 7, 8,
        9, 10, 11, 12, 9, 10, 11, 12,
        13, 14, 15, 16, 13, 14, 15, 16,
        1, 2, 3, 4, 1, 2, 3, 4,
        5, 6, 7, 8, 5, 6, 7, 8,
        9, 10, 11, 12, 9, 10, 11, 12,
        13, 14, 15, 16, 13, 14, 15, 16
    };
    B.origin = (struct pt) {1,1};
    B.nrow = 8;
    B.n = 8;
    print(B);
    printf("\n");

    struct matrix C;
    C = recursive_multiply(A, B);
    print(C);
    printf("\n");

    C = strassen_multiply(A, B);
    print(C);
    printf("\n");
}