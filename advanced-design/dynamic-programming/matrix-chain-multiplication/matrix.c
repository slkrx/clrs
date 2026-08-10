#ifndef MATRIX
#define MATRIX

typedef struct {
    int height, width;
    unsigned long int **scalars;
} matrix;

matrix *create_matrix(int height, int width) {
    matrix *M;
    int i;

    M = (matrix*) malloc(sizeof(matrix));
    M->height = height;
    M->width = width;
    M->scalars = (unsigned long int**) malloc(sizeof(unsigned long int*) * height);
    for (i = 0; i < height; i++)
        M->scalars[i] = (unsigned long int*) malloc(sizeof(unsigned long int) * width);
    return M;
}

matrix *create_matrix_from_array(int height, int width, unsigned long int *scalars) {
    matrix *M;
    int i, j;

    M = (matrix*) malloc(sizeof(matrix));
    M->height = height;
    M->width = width;
    M->scalars = (unsigned long int**) malloc(sizeof(unsigned long int*) * height);
    for (i = 0; i < height; i++) {
        M->scalars[i] = (unsigned long int*) malloc(sizeof(unsigned long int) * width);
        for (j = 0; j < width; j++) {
            M->scalars[i][j] = *(scalars + i * width + j);
        }
    }
    return M;
}

matrix *matrix_multiply(matrix *A, matrix *B) {
    matrix *C;
    int i, j, k;

    if (A->width != B->height) {
        printf("Matrix dimension mismatch");
        exit(1);
    }

    C = create_matrix(A->height, B->width);

    for (i = 0; i < A->height; i++) {
        for (j = 0; j < B->width; j++) {
            C->scalars[i][j] = 0;
            for (k = 0; k < B->height; k++)
                C->scalars[i][j] += A->scalars[i][k] * B->scalars[k][j];
        }
    }
    return C;
}

void print_matrix(matrix *A) {
    int i, j;

    for (i = 0; i < A->height; i++)
        for (j = 0; j < A->width; j++)
            printf("%lu%c", A->scalars[i][j], j == A->width - 1 ? '\n' : ' ');
}

#endif