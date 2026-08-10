#ifndef HASHTABLE
#define HASHTABLE

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    unsigned short deleted;
    void *elt;
} slot;

typedef struct {
    slot **table;
    int size;
} hash_table;

slot *create_slot() {
    slot *s = (slot *) malloc(sizeof(slot));
    s->deleted = 0;
    s->elt = NULL;
    return s;
}

hash_table *create_hash_table(int m) {
    hash_table *t = malloc(sizeof(hash_table));
    t->table = malloc(sizeof(slot *) * m);
    t->size = m;
    for (int i = 0; i < m; i++)
        t->table[i] = create_slot();
    return t;
}

int hash(hash_table *t, int k, int i) {
    return (k % t->size + i) % t->size;
    // return (k % t->size + i + (int)pow(3*i, 2)) % t->size;
    // return (k + i * (1 + k % (t->size - 1))) % t->size;
}

int hash_table_insert(hash_table *t, int k) {
    int i, j, *key;

    for (i = 0; i < t->size; i++) {
        j = hash(t, k, i);
        if (t->table[j]->deleted || t->table[j]->elt == NULL) {
            t->table[j]->deleted = 0;
            key = malloc(sizeof(int));
            *key = k;
            t->table[j]->elt = key;
            return j;
        }
    }
    fprintf(stderr, "hash table overflow");
    return -1;
}

slot *hash_table_search(hash_table *t, int k) {
    int i, j;

    for (i = 0; i < t->size; i++) {
        j = hash(t, k, i);
        if (t->table[j]->deleted)
            continue;
        else if (t->table[j]->elt == NULL)
            return NULL;
        else if (*(int*)t->table[j]->elt == k)
            return t->table[j];
    }
    return NULL;
}

void hash_table_delete(slot *s) {
    s->deleted = 1;
    free(s->elt);
    s->elt = NULL;
}

void print_hash_table(hash_table *t) {
    for (int i = 0; i < t->size; i++) {
        void *elt_ptr = t->table[i]->elt;
        printf ("%d | %d\n", i, elt_ptr == NULL ? 0 : *(int *)elt_ptr);
    }
}

#endif