#ifndef RBT
#define RBT

#include <stdlib.h>
#include <stdio.h>
#include "../stack/ptr_stack.c"

#define RED 0
#define BLACK 1

typedef struct node {
    struct node *p, *left, *right;
    int key, color;
} node;

typedef struct {
    node *root, *nil;
} rbtree;

rbtree *create_tree() {
    rbtree *t = (rbtree *) malloc(sizeof(rbtree));
    t->nil = (node *) malloc(sizeof(node));
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->p = NULL;
    t->nil->key = 0;
    t->nil->color = BLACK;
    t->root = t->nil;
    return t;
}

node *create_node(rbtree *T, int k) {
    node *n = (node *) malloc(sizeof(node));
    n->p = n->left = n->right = T->nil;
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

void print_tree_in_order(rbtree *T, node *p) {
    if (p == T->nil)
        return;
    print_tree_in_order(T, p->left);
    printf("%d ", p->key);
    print_tree_in_order(T, p->right);
}

void print_tree_iterative(rbtree *T, node *root) {
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
        while (p != T->nil) {
            ptr_stack_push(s, p);
            p = p->left;
        }
    }
}

void print_tree_preorder(rbtree *T, node *p) {
    if (p == T->nil)
        return;
    printf("%d ", p->key);
    print_tree_preorder(T, p->left);
    print_tree_preorder(T, p->right);
}

void print_tree_postorder(rbtree *T, node *p) {
    if (p == T->nil)
        return;
    print_tree_postorder(T, p->left);
    print_tree_postorder(T, p->right);
    printf("%d ", p->key);
}

node *tree_search(rbtree *T, node *x, int k) {
    if (x == T->nil || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(T, x->left, k);
    else
        return tree_search(T, x->right, k);
}

node *iterative_tree_search(rbtree *T, node *x, int k) {
    while (x != T->nil && k != x->key)
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    return x;
}

node *tree_minimum(rbtree *T, node *x) {
    while (x->left != T->nil)
        x = x->left;
    return x;
}

node *tree_minimum_recursive(rbtree *T, node *x) {
    if (x->left == T->nil)
        return x;
    return tree_minimum_recursive(T, x->left);
}

node *tree_maximum_recursive(rbtree *T, node *x) {
    if (x->right == T->nil)
        return x;
    return tree_maximum_recursive(T, x->right);
}

node *tree_maximum(rbtree *T, node *x) {
    while (x->right != T->nil)
        x = x->right;
    return x;
}

node *tree_successor(rbtree *T, node *x) {
    node *y;

    if (x->right != T->nil)
        return tree_minimum(T, x->right);
    y = x->p;
    while (y != T->nil && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

node *tree_predecessor(rbtree *T, node *x) {
    node *y;

    if (x->left != T->nil)
        return tree_maximum(T, x->left);
    y = x->p;
    while (y != T->nil && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}

void left_rotate(rbtree *T, node *x) {
    node *y;

    y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
        y->left->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
}

void right_rotate(rbtree *T, node *x) {
    node *y;

    y = x->left;
    x->left = y->right;
    if (y->right != T->nil)
        y->right->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
}

void rb_insert_fixup(rbtree *T, node *z) {
    node *y;

    while (z->p->color == RED)
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(T, z);
                } z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(T, z->p->p);
            }
        } else {
            y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(T, z);
                } z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(T, z->p->p);
            }
        }
    T->root->color = BLACK;
}

void rb_insert(rbtree *T, node *z) {
    node *x, *y;

    y = T->nil;
    x = T->root;
    while (x != T->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->p = y;
    if (y == T->nil)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else y->right = z;
    z->color = RED;
    rb_insert_fixup(T, z);
}

void rb_insert_key(rbtree *T, int k) {
    rb_insert(T, create_node(T, k));
}

void recursive_tree_insert(rbtree *T, node *root, node *x) {
    if (x->key < root->key)
        if (root->left == T->nil)
            set_left(root, x);
        else
            recursive_tree_insert(T, root->left, x);
    else
        if (root->right == T->nil)
            set_right(root, x);
        else
            recursive_tree_insert(T, root->right, x);
}

void recursive_tree_insert_key(rbtree *T, int k) {
    if (T->root == NULL)
        T->root = create_node(T, k);
    else
        recursive_tree_insert(T, T->root, create_node(T, k));
}

void rb_transplant(rbtree *T, node *u, node *v) {
    if (u->p == T->nil)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
}

void rb_delete_fixup(rbtree *T, node *x) {
    node *w;

    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(T, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p->right;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(T, x->p);
                x = T->root;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(T, x->p);
                w = x->p->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p->left;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void rb_delete(rbtree *T, node *z) {
    node *y, *x;
    int y_original_color;

    y = z;
    y_original_color = y->color;
    if (z->left == T->nil) {
        x = z->right;
        rb_transplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        rb_transplant(T, z, z->left);
    }
    else {
        y = tree_minimum(T, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->p == z)
            x->p = y;
        else {
            rb_transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        rb_transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (y_original_color == BLACK)
        rb_delete_fixup(T, x);
}

#endif