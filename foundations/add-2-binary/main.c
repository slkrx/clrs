#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *A, *B, *C;
    int n, i, carry, a, b, m;

    A = argv[1];
    B = argv[2];
    n = strlen(A);
    C = (char *) malloc(sizeof(char) * (n + 2));
    C[n+1] = '\0';
    carry = 0;

    for (i = n - 1; i >= 0; i--) {
        a = A[i] - '0';
        b = B[i] - '0';
        m = a + b + carry;

        switch(m) {
        case 3:
            C[i+1] = '1';
            carry = 1;
            break;
        case 2:
            C[i+1] = '0';
            carry = 1;
            break;
        case 1:
            C[i+1] = '1';
            carry = 0;
            break;
        case 0:
            C[i+1] = '0';
            carry = 0;
            break;
        }
    }

    C[0] = '0' + carry;

    printf("%s\n", C);
}