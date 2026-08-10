#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node *left, *right;
    int height;
    char *key;
} node;

typedef struct {
    node *root, *nil;
} bst;

bst *create_tree() {
    bst *T = (bst *) malloc(sizeof(bst));
    T->nil = (node *) malloc(sizeof(node));
    T->nil->left = NULL;
    T->nil->right = NULL;
    T->nil->key = NULL;
    T->nil->height = 0;
    T->root = T->nil;
    return T;
}

node *create_node(bst *T, char *key) {
    node *n = (node *) malloc(sizeof(node));
    n->left = n->right = T->nil;
    n->key = key;
    n->height = 1;
    return n;
}


void build_matrix(bst *T, node *x, char ***matrix, int row, int column, int h) {
    int offset;

    if (x == T->nil)
        return;
    offset = pow(2, h - row - 1);
    free(matrix[row][(offset + 1) * column + offset + (offset - 1) * column]);
    matrix[row][(offset + 1) * column + offset + (offset - 1) * column] = x->key;
    build_matrix(T, x->left, matrix, row + 1, column * 2, h);
    build_matrix(T, x->right, matrix, row + 1, column * 2 + 1, h);
}

void print_tree_visual(bst *t) {
    char ***matrix = (char ***) malloc(sizeof(char**) * t->root->height);
    for (int i = 0; i < t->root->height; i++) {
        matrix[i] = (char **) malloc(sizeof(char*) * pow(2, t->root->height));
        for (int j = 0; j < pow(2, t->root->height); j++) {
            matrix[i][j] = malloc(sizeof(char) * 2);
            matrix[i][j][0] = ' ';
            matrix[i][j][1] = '\0';
        }
    }
    build_matrix(t, t->root, matrix, 0, 0, t->root->height);
    for (int i = 0; i < t->root->height; i++) {
        for (int j = 0; j < pow(2, t->root->height); j++)
            printf("%2s", matrix[i][j]);
        putchar('\n');
    }
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

char *itok(int r, char c) {
    char *s, *suffix;
    int n;

    n = (int) r == 0 ? 1 : log10(r) + 1;
    s = (char *) malloc(sizeof(char) * (n + 2));
    s[0] = c;
    s[1] = '\0';
    suffix = (char *) malloc(sizeof(char) * (n + 1));
    itoa(r, suffix);
    strcat(s, suffix);
    return s;
}