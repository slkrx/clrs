#include "lwp.c"
#include <stdio.h>
#include <stdlib.h>
#include "list.c"

int main() {
    float **E, *r, sol;
    int n, m, i, j, *sources;
    list **edge_list;
    edge **edges;

    n = 11;
    E = (float**) malloc(sizeof(float*) * n);
    r = (float*) malloc(sizeof(float) * n);
    for (i = 0; i < n; i++) {
        r[i] = __FLT_MIN__;
        E[i] = (float*) malloc(sizeof(float) * n);
        for (j = 0; j < n; j++)
            E[i][j] = 0.0;
    }
    E[0][1] = 3.0;
    E[0][2] = 5.0;
    E[0][3] = 5.0;
    E[1][4] = 2.0;
    E[2][4] = 6.0;
    E[3][5] = 12.0;
    E[4][7] = 5.0;
    E[4][8] = 3.0;
    E[4][9] = 2.0;
    E[5][2] = 5.0;
    E[7][10] = 1.0;
    E[8][10] = 2.0;
    E[9][10] = 5.0;

    lwp_memoized(E, 0, 10, n, r);

    m = 13;
    edge_list = (list**) malloc(sizeof(list*) * n);
    sources = (int *) malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        edge_list[i] = create_list();
    edges = (edge**) malloc(sizeof(edge*) * n);
    edges[0] = create_edge(0,1,3.0);
    edges[1] = create_edge(0,2,5.0);
    edges[2] = create_edge(0,3,5.0);
    edges[3] = create_edge(1,4,2.0);
    edges[4] = create_edge(2,4,6.0);
    edges[5] = create_edge(3,5,12.0);
    edges[6] = create_edge(4,7,5.0);
    edges[7] = create_edge(4,8,3.0);
    edges[8] = create_edge(4,9,2.0);
    edges[9] = create_edge(5,2,5.0);
    edges[10] = create_edge(7,10,1.0);
    edges[11] = create_edge(8,10,2.0);
    edges[12] = create_edge(9,10,5.0);
    for (i = 0; i < m; i++)
        list_insert(edge_list[edges[i]->target], create_node(edges[i]));
    lwp_memoized_(edge_list, 0, 10, r, sources);
    printf("%0.2f\n", r[n-1]);
    printf("%d ", n);
    i = n - 1;
    while (i > 0) {
        printf("%d ", sources[i]);
        i = sources[i];
    }
}