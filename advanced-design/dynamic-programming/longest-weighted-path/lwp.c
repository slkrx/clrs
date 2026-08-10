#include <limits.h>
#include "list.c"

float lwp_recursive(float **E, int s, int t, int n) {
    float max;
    int i, j, v;

    if (s == t)
        return 0.0;

    max = __FLT_MIN__;
    for (i = 0; i < n; i++) {
        if (E[i][t] > 0.0) {
            v = lwp_recursive(E, s, i, n);
            if (v + E[i][t] > max)
                max = v + E[i][t];
        }
    }
    return max;
}

void lwp_memoized(float **E, int s, int t, int n, float *r) {
    float max;
    int i, j, v;

    if (s == t)
        r[t] = 0.0;

    max = __FLT_MIN__;
    for (i = 0; i < n; i++) {
        if (E[i][t] > 0.0) {
            if (r[t] > __FLT_MIN__)
                v = r[t];
            else
                v = lwp_recursive(E, s, i, n);
            if (v + E[i][t] > max)
                max = v + E[i][t];
        }
    }
    r[t] = max;
}

void lwp_memoized_(list **E, int s, int t, float *r, int *sources) {
    float max;
    int i, j, v;
    node *x;

    if (s == t)
        r[t] = 0.0;
    
    max = __FLT_MIN__;
    x = E[t]->head;
    while (x != NULL) {
        if (r[x->key->source] == __FLT_MIN__)
            lwp_memoized_(E, s, x->key->source, r, sources);
        v = r[x->key->source];
        if (v + x->key->weight > max) {
            max = v + x->key->weight;
            sources[t] = x->key->source;
        }
        x = x->next;
    }
    r[t] = max;
}