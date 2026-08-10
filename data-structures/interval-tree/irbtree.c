#ifndef IRBT
#define IRBT

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define RED 0
#define BLACK 1
#define MAX(X,Y) (((X) >= (Y)) ? (X) : (Y))
#define OVERLAPS(X, Y) ((X).low <= (Y).high && (Y).low <= (X).high)
#define OPEN_OVERLAPS(X, Y) ((X).low < (Y).high && (Y).low < (X).high)

typedef struct {
    int low, high;
} interval;

typedef struct node {
    struct node *p, *left, *right;
    int color, height, max;
    interval i;
} node;

typedef struct {
    node *root, *nil;
} irbtree;

irbtree *create_tree() {
    irbtree *t = (irbtree *) malloc(sizeof(irbtree));
    t->nil = (node *) malloc(sizeof(node));
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->p = NULL;
    t->nil->color = BLACK;
    t->nil->height = 0;
    t->nil->max = INT_MIN;
    t->root = t->nil;
    return t;
}

node *create_node(irbtree *T, interval i) {
    node *n = (node *) malloc(sizeof(node));
    n->p = n->left = n->right = T->nil;
    n->height = 1;
    n->i.low = i.low;
    n->i.high = i.high;
    n->max = i.high;
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

void left_rotate(irbtree *T, node *x) {
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

    y->height = MAX(y->left->height, y->right->height) + 1;
    x->height = MAX(x->left->height, x->right->height) + 1;
    y->max = MAX(MAX(y->i.high, y->left->max), y->right->max);
    x->max = MAX(MAX(x->i.high, x->left->max), x->right->max);
}

void right_rotate(irbtree *T, node *x) {
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

    y->height = MAX(y->left->height, y->right->height) + 1;
    x->height = MAX(x->left->height, x->right->height) + 1;
    y->max = MAX(MAX(y->i.high, y->left->max), y->right->max);
    x->max = MAX(MAX(x->i.high, x->left->max), x->right->max);
}

void rb_insert_fixup(irbtree *T, node *z) {
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

void rb_insert(irbtree *T, node *z) {
    node *x, *y, *w;

    y = T->nil;
    x = T->root;
    while (x != T->nil) {
        y = x;
        if (z->i.low < x->i.low) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == T->nil)
        T->root = z;
    else if (z->i.low < y->i.low)
        y->left = z;
    else y->right = z;
    while (y != T->nil) {
        y->height = MAX(y->left->height, y->right->height) + 1;
        y->max = MAX(MAX(y->i.high, y->left->max), y->right->max);
        y = y->p;
    }
    z->color = RED;
    rb_insert_fixup(T, z);
}

void insert(irbtree *T, interval i) {
    rb_insert(T, create_node(T, i));
}

void rb_transplant(irbtree *T, node *u, node *v) {
    if (u->p == T->nil)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
}

void rb_delete_fixup(irbtree *T, node *x) {
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
                x = x->p;
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
                x = x->p;
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

node *tree_minimum(irbtree *T, node *x) {
    if (x->left == T->nil)
        return x;
    return tree_minimum(T, x->left);
}

void rb_delete(irbtree *T, node *z) {
    node *y, *x, *w;
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
    w = x->p;
    while (w != T->nil) {
        w->height = MAX(w->left->height, w->right->height) + 1;
        w->max = MAX(MAX(w->i.high, w->left->max), w->right->max);
        w = w->p;
    }
    if (y_original_color == BLACK)
        rb_delete_fixup(T, x);
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

void build_matrix(irbtree *T, node *x, char ***matrix, int row, int column, int h) {
    char *str, *str1, *str2, *tmpstr;
    int offset, n, m;

    if (x == T->nil)
        return;
    offset = pow(2, h - row - 1);
    n = (int) x->i.low == 0 ? 0 : log10(x->i.low);
    m = (int) x->i.high == 0 ? 0 : log10(x->i.high);
    str1 = (char *) malloc(sizeof(char) * ((int) n + 2));
    str2 = (char *) malloc(sizeof(char) * ((int) m + 2));
    itoa(x->i.low, str1);
    itoa(x->i.high, str2);
    if (x->color == RED) {
        str = (char *) malloc(sizeof(char) * ((int) n + m + 2 + 3 + 17));
        strcpy(str, "\033[0;31m[");
        strcat(str, str1);
        strcat(str, ",");
        strcat(str, str2);
        strcat(str, "]\033[0m");
    } else {
        str = (char *) malloc(sizeof(char) * ((int) n + m + 2 + 3));
        strcpy(str, "[");
        strcat(str, str1);
        strcat(str, ",");
        strcat(str, str2);
        strcat(str, "]");
    }

    free(matrix[row][(offset + 1) * column + offset + (offset - 1) * column]);
    matrix[row][(offset + 1) * column + offset + (offset - 1) * column] = str;
    build_matrix(T, x->left, matrix, row + 1, column * 2, h);
    build_matrix(T, x->right, matrix, row + 1, column * 2 + 1, h);
}

void print_tree_visual(irbtree *t) {
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
            printf("%7s", matrix[i][j]);
        putchar('\n');
    }
}

node *search(irbtree *T, interval i) {
    node *x;

    x = T->root;
    while (x != T->nil && !OVERLAPS(i, x->i))
        if (x->left != T->nil && x->left->max >= i.low)
            x = x->left;
        else x = x->right;
    return x;
}

node *min_overlap(irbtree *T, interval i) {
    node *x, *y;

    y = T->nil;
    x = T->root;
    while (x != T->nil) {
        if (OVERLAPS(i, x->i) && (y == T->nil || x->i.low < y->i.low))
            y = x;
        if (x->left != T->nil && x->left->max >= i.low)
            x = x->left;
        else x = x->right;
    }
    return y;
}

node *open_search(irbtree *T, interval i) {
    node *x;

    x = T->root;
    while (x != T->nil && !OPEN_OVERLAPS(i, x->i))
        if (x->left != T->nil && x->left->max > i.low)
            x = x->left;
        else x = x->right;
    return x;
}

void span(irbtree *T, node *x, interval i) {
    if (OVERLAPS(i, x->i))
        printf("[%d,%d]\n", x->i.low, x->i.high);
    if (x->left != T->nil && x->left->max > i.low)
        span(T, x->left, i);
    if (x->right != T->nil && x->right->max > i.low)
        span(T, x->right, i);
}

void spanning_overlap(irbtree *T, interval i) {
    return span(T, T->root, i);
}

node *exact_search(irbtree *T, interval i) {
    node *x;

    x = T->root;
    while (x != T->nil) {
        if (i.low == x->i.low && i.high == x->i.high)
            return x;
        if (x->left != T->nil && x->left->max >= i.low)
            x = x->left;
        else x = x->right;
    }
    return x;
}

#endif