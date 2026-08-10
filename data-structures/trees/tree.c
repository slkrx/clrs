#ifndef TREE
#define TREE

#include <stdlib.h>
#include <stdio.h>
#include "../stack/ptr_stack.c"

typedef struct node {
    struct node *p, *left, *right;
    int key;
} node;

typedef struct {
    node *root;
} tree;

tree *create_tree() {
    tree *t = (tree *) malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

node *create_node(int k) {
    node *n = (node *) malloc(sizeof(node));
    n->p = n->left = n->right = NULL;
    n->key = k;
    return n;
}

node *set_left(node *a, node *b) {
    a->left = b;
    b->p = a;
    return b;
}

node *set_right(node *a, node *b) {
    a->right = b;
    b->p = a;
    return b;
}

void print_tree_in_order(node *p) {
    if (p == NULL)
        return;
    print_tree_in_order(p->left);
    printf("%d ", p->key);
    print_tree_in_order(p->right);
}

void print_tree(tree *t) {
    print_tree_in_order(t->root);
    putchar('\n');
}

void print_tree_iterative(tree *t) {
    node *p;
    ptr_stack *s;

    s = create_ptr_stack(20);
    ptr_stack_push(s, t->root);

    while (!ptr_stack_empty(s)) {
        p = (node *) ptr_stack_pop(s);
        if (p == NULL)
            continue;
        printf("%d ", p->key);
        ptr_stack_push(s, p->right);
        ptr_stack_push(s, p->left);
    }
    putchar('\n');
}

#endif