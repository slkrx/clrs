#ifndef OST
#define OST

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define RED 0
#define BLACK 1
#define MAX(X,Y) (((X) >= (Y)) ? (X) : (Y))

int inv = 0;

typedef struct node {
    struct node *p, *left, *right, *min, *max, *successor, *predecessor;
    int key, color, size, height, bh;
} node;

typedef struct {
    node *root, *nil;
} ostree;

ostree *create_tree() {
    ostree *t = (ostree *) malloc(sizeof(ostree));
    t->nil = (node *) malloc(sizeof(node));
    t->nil->left = NULL;
    t->nil->right = NULL;
    t->nil->p = NULL;
    t->nil->key = 0;
    t->nil->color = BLACK;
    t->nil->bh = 0;
    t->nil->size = 0;
    t->nil->height = 0;
    t->nil->min = t->nil;
    t->nil->max = t->nil;
    t->root = t->nil;
    return t;
}

node *create_node(ostree *T, int k) {
    node *n = (node *) malloc(sizeof(node));
    n->p = n->left = n->right = n->predecessor = n->successor = T->nil;
    n->max = n->min = n;
    n->key = k;
    n->size = 1;
    n->height = 1;
    n->bh = 1;
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


node *tree_search(ostree *T, node *x, int k) {
    if (x == T->nil || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(T, x->left, k);
    else
        return tree_search(T, x->right, k);
}

node *search(ostree *T, int k) {
    return tree_search(T, T->root, k);
}

void left_rotate(ostree *T, node *x) {
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
    if (y->left == T->nil)
        y->min = y;
    else
        y->min = y->left->min;
    if (y->right == T->nil)
        y->max = y;
    else
        y->max = y->right->max;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    y->height = MAX(y->left->height, y->right->height) + 1;
    x->height = MAX(x->left->height, x->right->height) + 1;
}

void right_rotate(ostree *T, node *x) {
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
    if (x->left == T->nil)
        x->min = x;
    else
        x->min = x->left->min;
    if (x->right == T->nil)
        x->max = x;
    else
        x->max = x->right->max;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    y->height = MAX(y->left->height, y->right->height) + 1;
    x->height = MAX(x->left->height, x->right->height) + 1;
}

void rb_insert_fixup(ostree *T, node *z) {
    node *y;

    while (z->p->color == RED)
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
                z->bh += 1;
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
                z->bh += 1;
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

void rb_insert(ostree *T, node *z) {
    node *x, *y, *w;

    y = T->nil;
    x = T->root;
    while (x != T->nil) {
        x->size += 1;
        y = x;
        if (z->key < x->key) {
            z->successor = x;
            x = x->left;
        } else {
            z->predecessor = x;
            x = x->right;
        }
    }
    z->p = y;
    if (y == T->nil)
        T->root = z;
    else if (z->key < y->key)
        y->left = z;
    else y->right = z;
    w = y;
    while (w != T->nil) {
        if (w->left != T->nil) {
            w->min = w->left->min;
            w->predecessor = w->left->max;
        }
        if (w->right != T->nil) {
            w->max = w->right->max;
            w->successor = w->right->min;
        }
        w->height = MAX(w->left->height, w->right->height) + 1;
        w = w->p;
    }
    z->color = RED;
    rb_insert_fixup(T, z);
}

void insert(ostree *T, int k) {
    rb_insert(T, create_node(T, k));
}

void rb_transplant(ostree *T, node *u, node *v) {
    if (u->p == T->nil)
        T->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
    v->size = u->size;
    if (u->left == T->nil)
        v->min = v;
    else
        v->min = u->min;
    if (u->right == T->nil)
        v->max = v;
    else
        v->max = u->max;
}

void rb_delete_fixup(ostree *T, node *x) {
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
                x->bh -= 1;
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
                x->p->bh -= 1;
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
                x->bh -= 1;
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
                x->p->bh -= 1;
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

node *tree_minimum(node *x) {
    return x->min;
}

node *tree_maximum(node *x) {
    return x->max;
}

void rb_delete(ostree *T, node *z) {
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
        y = z->successor;
        y_original_color = y->color;
        y->bh = z->bh;
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
    z->predecessor->successor = z->successor;
    z->successor->predecessor = z->predecessor;
    w = x->p;
    while (w != T->nil) {
        if (w->left == T->nil)
            w->min = w;
        else
            w->min = w->left->min;
        if (w->right == T->nil)
            w->max = w;
        else
            w->max = w->right->max;
        w->size -= 1;
        w->height = MAX(w->left->height, w->right->height) + 1;
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

void build_matrix(ostree *T, node *x, char ***matrix, int row, int column, int h) {
    char *str, *tmpstr;
    int offset;

    if (x == T->nil)
        return;
    offset = pow(2, h - row - 1);
    if (x->color == RED) {
        str = (char *) malloc(sizeof(char) * (int) log10(x->key) + 2 + 17);
        tmpstr = (char *) malloc(sizeof(char) * (int) log10(x->key) + 2);
        itoa(x->key, tmpstr);
        strcpy(str, "\033[0;31m");
        strcat(str, tmpstr);
        strcat(str, "\033[0m");
    } else {
        str = (char *) malloc(sizeof(char) * (int) log10(x->key) + 2);
        itoa(x->key, str);
    }

    free(matrix[row][(offset + 1) * column + offset + (offset - 1) * column]);
    matrix[row][(offset + 1) * column + offset + (offset - 1) * column] = str;
    build_matrix(T, x->left, matrix, row + 1, column * 2, h);
    build_matrix(T, x->right, matrix, row + 1, column * 2 + 1, h);
}

void print_tree_visual(ostree *t) {
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

void print_tree_inorder(ostree *t, node *n) {
    if (n == t->nil)
        return;
    print_tree_inorder(t, n->left);
    printf("%d ", n->key);
    print_tree_inorder(t, n->right);
}

node *os_select(node *x, int i) {
    int r;

    r = x->left->size + 1;
    if (i == r)
        return x;
    else if (i < r)
        return os_select(x->left, i);
    else
        return os_select(x->right, i - r);
}

node *select(ostree *t, int i) {
    return os_select(t->root, i);
}

node *iterative_select(ostree *t, int i) {
    int r;
    node *x;

    x = t->root;
    do {
        r = x->left->size + 1;
        if (i < r)
            x = x->left;
        else if (i > r) {
            x = x->right;
            i -= r;
        }
    } while (i != r);

    return x;
}

int rank(ostree *T, node *x) {
    int r;
    node *y;

    r = x->left->size + 1;
    y = x;
    while (y != T->root) { 
        if (y == y->p->right)
            r = r + y->p->left->size + 1;
        y = y->p;
    }
    return r;
}

int _recursive_rank(node *x, int key) {
    if (x->key == key)
        return 1 + x->left->size;
    else if (key > x->key)
        return 1 + x->left->size + _recursive_rank(x->right, key);
    else
        return _recursive_rank(x->left, key);
}

int recursive_rank(ostree *t, int key) {
    return _recursive_rank(t->root, key);
}

#endif