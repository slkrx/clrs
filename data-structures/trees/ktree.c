#ifndef KTREE
#define KTREE

#include <stdlib.h>
#include <stdio.h>
#include "../stack/ptr_stack.c"

typedef struct knode {
    struct knode *p, *left_child, *right_sibling;
    int key;
} knode;

typedef struct {
    knode *root;
} ktree;

ktree *create_ktree() {
    ktree *t = (ktree *) malloc(sizeof(ktree));
    t->root = NULL;
    return t;
}

knode *create_knode(int k) {
    knode *n = (knode *) malloc(sizeof(knode));
    n->p = n->left_child = n->right_sibling = NULL;
    n->key = k;
    return n;
}

knode *set_left_child(knode *a, knode *b) {
    a->left_child = b;
    b->p = a;
    return b;
}

knode *set_right_sibling(knode *a, knode *b) {
    a->right_sibling = b;
    b->p = a->p;
    return b;
}

void print_ktree(ktree *t) {
    knode *p;
    ptr_stack *s;

    s = create_ptr_stack(20);
    ptr_stack_push(s, t->root);

    while (!ptr_stack_empty(s)) {
        p = (knode *) ptr_stack_pop(s);
        if (p == NULL)
            continue;
        printf("%d ", p->key);
        ptr_stack_push(s, p->left_child);
        ptr_stack_push(s, p->right_sibling);
    }
    putchar('\n');
}

#endif