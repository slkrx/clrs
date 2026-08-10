#include <stdlib.h>
#include "bitonic.c"

int main() {
    point p[] = { {0,6}, {1,0}, {2,3}, {5,4}, {6,1}, {7,5}, {8,2} };
    int n = 6;
    printf("%02f\n", bitonic_length_recursive(p, n - 1));
}