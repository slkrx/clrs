#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum Operation {
    COPY,
    REPLACE,
    DELETE,
    INSERT,
    TWIDDLE,
    KILL
};

typedef struct {
    int i,j;
} pair;

typedef struct {
    pair min_pair;
    float **c;
    int **ops;
} solution;

char *op_to_s(int i) {
    switch (i) {
        case COPY:
            return "COPY";
        case REPLACE:
            return "REPLACE";
        case DELETE:
            return "DELETE";
        case INSERT:
            return "INSERT";
        case TWIDDLE:
            return "TWIDDLE";
        case KILL:
            return "KILL";
        default:
            return "";
    }
}

void print_solution_recursive(int **ops, int i, int j) {
    if (i == 0 && j > 0) {
        for (int k = 0; k < j; k++)
            printf("INSERT ");
        return;
    }
    if (i <= 0 && j <= 0)
        return;
    switch (ops[i][j]) {
        case COPY:
        case REPLACE:
            print_solution_recursive(ops, i-1, j-1);
            break;
        case DELETE:
            print_solution_recursive(ops, i-1, j);
            break;
        case INSERT:
            print_solution_recursive(ops, i, j-1);
            break;
        case TWIDDLE:
            print_solution_recursive(ops, i-2, j-2);
            break;
    }
    printf("%s ", op_to_s(ops[i][j]));
}

void print_solution(int **ops, pair min_pair, int m, int n) {
    int i, j;

    print_solution_recursive(ops, min_pair.i, min_pair.j);
    if (min_pair.j == n && min_pair.i != m)
        printf("%s\n", "KILL");
    else if (min_pair.i == m && min_pair.j != n)
        while (min_pair.j++ < n)
            printf("%s%c", "INSERT", min_pair.j == n + 1 ? '\n' : ' ');
    else
        putchar('\n');
}

solution *edit_distance(char *x, char *y, float *cost) {
    int i, j, n, m, **ops, min_op;
    float **c, twiddle_cost, copy_cost, replace_cost, delete_cost, insert_cost, min_cost, temp_cost;
    n = m = 0;
    pair min_pair;
    solution *s = (solution*) malloc(sizeof(solution));

    for (i = 0; x[i] != '\0'; i++)
        m++;
    for (i = 0; y[i] != '\0'; i++)
        n++;
    c = (float**) malloc(sizeof(float*) * (m + 1));
    ops = (int**) malloc(sizeof(int*) * (m + 1));
    for (i = 0; i <= m; i++) {
        c[i] = (float*) malloc(sizeof(float) * (n + 1));
        ops[i] = (int*) malloc(sizeof(int) * (n + 1));
    }

    c[0][0] = 0;
    for (j = 1; j <= n; j++)
        c[0][j] = j * cost[INSERT];
    for (i = 1; i <= m; i++)
        c[i][0] = i * cost[DELETE];

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            min_cost = __FLT_MAX__;
            if ((temp_cost = cost[INSERT] + c[i][j-1]) < min_cost) {
                min_cost = temp_cost;
                min_op = INSERT;
            } if ((temp_cost = cost[DELETE] + c[i-1][j]) < min_cost) {
                min_cost = temp_cost;
                min_op = DELETE;
            } if ((temp_cost = cost[REPLACE] + c[i-1][j-1]) < min_cost) {
                min_cost = temp_cost;
                min_op = REPLACE;
            } if (x[i-1] == y[j-1])
                if ((temp_cost = cost[COPY] + c[i-1][j-1]) < min_cost) {
                    min_cost = temp_cost;
                    min_op = COPY;
                }
            if (i > 1 && j > 1 && x[i-2] == y[j-1] && x[i-1] == y[j-2])
                if ((temp_cost = cost[TWIDDLE] + c[i-2][j-2]) < min_cost) {
                    min_cost = temp_cost;
                    min_op = TWIDDLE;
                }
            c[i][j] = min_cost;
            ops[i][j] = min_op;
        }
    }
    min_cost = __FLT_MAX__;
    for (j = 0; j <= n - 1; j++)
        if ((temp_cost = cost[INSERT] * (n - j) + c[m][j]) < min_cost) {
            min_cost = temp_cost;
            min_pair.i = m;
            min_pair.j = j;
        }
    for (i = 0; i <= m - 1; i++)
        if ((temp_cost = cost[KILL] + c[i][n]) < min_cost) {
            min_cost = temp_cost;
            min_pair.i = i;
            min_pair.j = n;
        }
    if ((temp_cost = c[m][n]) < min_cost) {
        min_cost = temp_cost;
        min_pair.i = m;
        min_pair.j = n;
    }
    s->min_pair = min_pair;
    s->c = c;
    s->ops = ops;
    return s;
}

float edit_distance_recursive(char *x, char *y, int i, int j, int m, int n, float *cost, char **o, float **c) {
    float twiddle_cost, copy_cost, insert_cost, delete_cost, replace_cost, min;

    if (i < 0 && j < 0)
        return 0.0;
    if (i < 0)
        return cost[INSERT] + edit_distance_recursive(x, y, i, j-1, m, n, cost, o, c);
    if (j < 0)
        return 0.0;

    if (i > 0 && j > 0 && x[i-1] == y[j] && x[i] == y[j-1])
        twiddle_cost = cost[TWIDDLE] + 
            edit_distance_recursive(x, y, i-2, j-2, m, n, cost, o, c);
    else
        twiddle_cost = __FLT_MAX__;
    
    if (x[i] == y[j])
        copy_cost = cost[COPY] + edit_distance_recursive(x, y, i-1, j-1, m, n, cost, o, c);
    else
        copy_cost = __FLT_MAX__;

    insert_cost = cost[INSERT] + edit_distance_recursive(x, y, i, j-1, m, n, cost, o, c);
    delete_cost = cost[DELETE] + edit_distance_recursive(x, y, i-1, j, m, n, cost, o, c);
    replace_cost = cost[REPLACE] + edit_distance_recursive(x, y, i-1, j-1, m, n, cost, o, c);

    min = fmin(twiddle_cost, fmin(copy_cost, fmin(insert_cost,
        fmin(delete_cost, replace_cost))));
    if (min == twiddle_cost)
        o[i][j] = 't';
    else if (min == copy_cost)
        o[i][j] = 'c';
    else if (min == insert_cost)
        o[i][j] = 'i';
    else if (min == delete_cost)
        o[i][j] = 'd';
    else
        o[i][j] = 'r';
    c[i][j] = min;
    return min;
}