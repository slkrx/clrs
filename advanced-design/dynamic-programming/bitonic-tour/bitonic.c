#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>

typedef struct {
    int x, y;
} point;

typedef struct {
    float **b;
    int **r;
} solution;

float distance(point x, point y) {
    return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}

solution *shortest_bitonic_tour(point *p, int n) {
    float **b, q;
    int **r, i, j, k;
    solution *s;

    b = (float**) malloc(sizeof(float*) * n);
    r = (int**) malloc(sizeof(int*) * n);
    s = (solution*) malloc(sizeof(solution));

    for (i = 0; i < n; i++) {
        b[i] = (float*) malloc(sizeof(float) * n);
        r[i] = (int*) malloc(sizeof(int) * n);
    }

    b[0][1] = distance(p[0], p[1]);

    for (j = 2; j < n; j++) {
        for (i = 0; i < j - 1; i++) {
            b[i][j] = b[i][j-1] + distance(p[j-1], p[j]);
            r[i][j] = j - 1;
        }
        b[j-1][j] = INT_MAX;
        for (k = 0; k < j - 1; k++) {
            q = b[k][j-1] + distance(p[k], p[j]);
            if (q < b[j-1][j]) {
                b[j-1][j] = q;
                r[j-1][j] = k;
            }
        }
    }
    b[n-1][n-1] = b[n-2][n-1] + distance(p[n-2], p[n-1]);

    s->b = b;
    s->r = r;
    return s;
}