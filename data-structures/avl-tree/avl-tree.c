#ifndef AVL
#define AVL

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX(X,Y) (((X) >= (Y)) ? (X) : (Y))

typedef struct node {
    struct node *p, *left, *right;
    int key, height;
} node;

typedef struct {
    node *root;
} avltree;

avltree *create_tree() {
    avltree *p = (avltree *) malloc(sizeof(avltree));
    p->root = NULL;
    return p;
}

node *create_node(int k) {
    node *n = (node *) malloc(sizeof(node));
    n->p = n->left = n->right = NULL;
    n->key = k;
    n->height = 1;
    return n;
}

int height(node *x) {
    if (x == NULL)
        return 0;
    else
        return x->height;
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

node *tree_search(node *x, int k) {
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(x->left, k);
    else
        return tree_search(x->right, k);
}

void print_tree_inorder(node *x) {
    if (x == NULL)
        return;
    print_tree_inorder(x->left);
    printf("%d ", x->key);
    print_tree_inorder(x->right);
}

void itoa(int n, char s[]) {
    int temp, i, j, digit;
    j = 0;

    for (temp = n, i = 0; temp != 0; ++i, temp /= 10)
        ;

    if (n < 0)
        s[j++] = '-';

    do {
        --i;
        digit = n / pow(10, i);
        s[j++] = (digit < 0 ? digit * -1 : digit) + '0';
        n -= digit * pow(10, i);
    } while (i > 0);

    s[j] = '\0';
}

void build_matrix(node *x, char ***matrix, int row, int column, int h) {
    if (x == NULL)
        return;
    int offset = pow(2, h - row - 1);
    char *str = (char *) malloc(sizeof(char) * (int) log10(x->key) + 2);
    itoa(x->key, str);

    free(matrix[row][(offset + 1) * column + offset + (offset - 1) * column]);
    matrix[row][(offset + 1) * column + offset + (offset - 1) * column] = str;
    build_matrix(x->left, matrix, row + 1, column * 2, h);
    build_matrix(x->right, matrix, row + 1, column * 2 + 1, h);
}

void print_tree_visual(avltree *t) {
    char ***matrix = (char ***) malloc(sizeof(char**) * t->root->height);
    for (int i = 0; i < t->root->height; i++) {
        matrix[i] = (char **) malloc(sizeof(char*) * pow(2, t->root->height));
        for (int j = 0; j < pow(2, t->root->height); j++) {
            matrix[i][j] = malloc(sizeof(char) * 2);
            matrix[i][j][0] = ' ';
            matrix[i][j][1] = '\0';
        }
    }
    build_matrix(t->root, matrix, 0, 0, t->root->height);
    for (int i = 0; i < t->root->height; i++) {
        for (int j = 0; j < pow(2, t->root->height); j++)
            printf("%2s", matrix[i][j]);
        putchar('\n');
    }
}

node *left_rotate(avltree *T, node *x) {
    node *y;

    y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->p = x;
    y->p = x->p;
    if (x->p == NULL)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->left = x;
    x->p = y;
    x->height = 1 + MAX(height(x->left), height(x->right));
    y->height = 1 + MAX(height(y->left), height(y->right));
    return y;
}

node *right_rotate(avltree *T, node *x) {
    node *y;

    y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->p = x;
    y->p = x->p;
    if (x->p == NULL)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;
    y->right = x;
    x->p = y;
    x->height = 1 + MAX(height(x->left), height(x->right));
    y->height = 1 + MAX(height(y->left), height(y->right));
    return y;
}

node *recursive_tree_insert(avltree *T, node *root, node *x) {
    if (root == NULL)
        return x;

    if (x->key < root->key)
        root->left = recursive_tree_insert(T, root->left, x);
    else
        root->right = recursive_tree_insert(T, root->right, x);
    root->height = 1 + MAX(height(root->left), height(root->right));

    if (abs(height(root->left) - height(root->right)) > 1) {
        if (height(root->left) - height(root->right) > 1) {
            if (height(root->left->left) > height(root->left->right)) {
                root = right_rotate(T, root);
            } else {
                left_rotate(T, root->left);
                root = right_rotate(T, root);
            }
        } else  {
            if (height(root->right->right) > height(root->right->left)) {
                root = left_rotate(T, root);
            } else {
                right_rotate(T, root->right);
                root = left_rotate(T, root);
            }
        }
    }
    return root;
}

void insert(avltree *t, node *x) {
    t->root = recursive_tree_insert(t, t->root, x);
}

void print_tree_preorder(node *p) {
    if (p == NULL)
        return;
    printf("%d ", p->key);
    print_tree_preorder(p->left);
    print_tree_preorder(p->right);
}

#endif