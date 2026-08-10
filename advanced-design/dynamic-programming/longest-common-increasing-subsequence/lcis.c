#include "/Users/samuelrechsteiner/src/clrs/data-structures/linked-lists/singly_linked.c"
#include <limits.h>

int last_smaller_elt_index(int *B, int x, int n) {
    int i, j, k;

    i = 0;
    j = n - 1;
    while(1) {
        if (i >= j)
            return i;
        k = (i + j + 1) / 2;
        if (B[k] >= x)
            j = k - 1;
        else
            i = k;
    }
}

void longest_monotonic(int *A, int n) {
    int *B, i, L, j;
    list **C;

    L = 0;
    B = (int*) malloc(sizeof(int) * n);
    C = (list**) malloc(sizeof(list*) * n);
    for (i = 0; i < n; i++) {
        B[i] = INT_MAX;
        C[i] = create_list();
    }
    for (i = 0; i < n; i++)
        if (A[i] < B[0]) {
            B[0] = A[i];
            C[0] = create_list();
            list_insert(C[0], create_node(A[i]));
        } else {
            j = last_smaller_elt_index(B, A[i], L + 1);
            B[j+1] = A[i];
            C[j+1]->head = C[j]->head;
            list_insert(C[j+1], create_node(A[i]));
            if (j + 1 > L)
                L++;
        }
    print_list(C[L]);
}
