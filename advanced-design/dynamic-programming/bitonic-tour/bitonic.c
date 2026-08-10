#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int x, y;
} point;

float distance(point x, point y) {
    return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}

float bitonic_length_recursive(point *p, int r) {
    if (r == 0)
        return 0.0;
    if (r == 1)
        return 2 * distance(p[0], p[1]);
    
    return bitonic_length_recursive(p, r - 1) + distance(p[r-1], p[r]) +
        distance(p[r-2], p[r]) - distance(p[r-2], p[r-1]);
}