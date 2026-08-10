#ifndef HASHTABLE
#define HASHTABLE

#include <stdlib.h>
#include "../linked-lists/xor/doubly_linked.c"

typedef struct {
    list **table;
    int size;
} hash_table;

hash_table *create_hash_table(int m) {
    hash_table *t = malloc(sizeof(hash_table));
    t->table = malloc(sizeof(void *) * m);
    t->size = m;
    for (int i = 0; i < m; i++)
        t->table[i] = create_list();
    return t;
}

int hash(hash_table *t, int k) {
    return k % t->size;
}

void hash_table_insert(hash_table *t, int k) {
    list_insert(t->table[hash(t, k)], create_node(k));
}

void print_hash_table(hash_table *t) {
    for (int i = 0; i < t->size; i++) {
        printf ("%d | ", i);
        print_list(t->table[i]);
    }
}

#endif