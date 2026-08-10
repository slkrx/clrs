#ifndef BST
#define BST

#include <stdlib.h>
#include <stdio.h>
#include "../stack/ptr_stack.c"

typedef struct node {
    struct node *p, *left, *right;
    int key;
} node;

typedef struct {
    node *root;
} btree;

btree *create_tree() {
    btree *p = (btree *) malloc(sizeof(btree));
    p->root = NULL;
    return p;
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

void print_tree_iterative(node *root) {
    node *p;
    ptr_stack *s;

    s = create_ptr_stack(20);
    
    p = root;
    while (p != NULL) {
        ptr_stack_push(s, p);
        p = p->left;
    }
    while (!ptr_stack_empty(s)) {
        p = ptr_stack_pop(s);
        printf("%d ", p->key);
        p = p->right;
        while (p != NULL) {
            ptr_stack_push(s, p);
            p = p->left;
        }
    }
}

void print_tree_preorder(node *p) {
    if (p == NULL)
        return;
    printf("%d ", p->key);
    print_tree_preorder(p->left);
    print_tree_preorder(p->right);
}

void print_tree_postorder(node *p) {
    if (p == NULL)
        return;
    print_tree_postorder(p->left);
    print_tree_postorder(p->right);
    printf("%d ", p->key);
}

node *tree_search(node *x, int k) {
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(x->left, k);
    else
        return tree_search(x->right, k);
}

node *iterative_tree_search(node *x, int k) {
    while (x != NULL && k != x->key)
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    return x;
}

node *tree_minimum(node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

node *tree_minimum_recursive(node *x) {
    if (x->left == NULL)
        return x;
    return tree_minimum_recursive(x->left);
}

node *tree_maximum_recursive(node *x) {
    if (x->right == NULL)
        return x;
    return tree_maximum_recursive(x->right);
}

node *tree_maximum(node *x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

node *tree_successor(node *x) {
    node *y;

    if (x->right != NULL)
        return tree_minimum(x->right);
    y = x->p;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

node *tree_predecessor(node *x) {
    node *y;

    if (x->left != NULL)
        return tree_maximum(x->left);
    y = x->p;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}

void tree_insert(btree *T, node *z) {
    node *x, *y;

    y = NULL;
    x = T->root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->p = y;
    if (y == NULL)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else y->right = z;
}

void tree_insert_key(btree *T, int k) {
    tree_insert(T, create_node(k));
}

void recursive_tree_insert(node *root, node *x) {
    if (x->key < root->key)
        if (root->left == NULL)
            set_left(root, x);
        else
            recursive_tree_insert(root->left, x);
    else
        if (root->right == NULL)
            set_right(root, x);
        else
            recursive_tree_insert(root->right, x);
}

void recursive_tree_insert_key(btree *T, int k) {
    if (T->root == NULL)
        T->root = create_node(k);
    else
        recursive_tree_insert(T->root, create_node(k));
}

void transplant(btree *T, node *u, node *v) {
    if (u->p == NULL)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    if (v != NULL)
        v->p = u->p;
}

void tree_delete(btree *T, node *z) {
    node *y;

    if (z->left == NULL)
        transplant(T, z, z->right);
    else if (z->right == NULL)
        transplant(T, z, z->left);
    else {
        y = tree_minimum(z->right);
        if (y->p != z) {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

#endif