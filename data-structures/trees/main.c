#include <stdio.h>
#include "tree.c"
#include "ktree.c"
#include "../stack/ptr_stack.c"

int main() {
    tree *t = create_tree();
    node *x;
    t->root = create_node(18);
    x = set_left(t->root, create_node(12));
    set_left(x, create_node(7));
    x = set_right(x, create_node(4));
    set_left(x, create_node(5));
    x = set_right(t->root, create_node(10));
    set_left(x, create_node(2));
    set_right(x, create_node(21));
    print_tree(t);
    print_tree_iterative(t);

    ktree *k = create_ktree();
    k->root = create_knode(18);
    set_left_child(k->root, create_knode(12));
    set_left_child(k->root->left_child, create_knode(5));
    set_right_sibling(k->root->left_child, create_knode(7));
    set_right_sibling(k->root->left_child->left_child, create_knode(10));
    set_left_child(k->root->left_child->left_child->right_sibling, create_knode(44));
    set_left_child(k->root->left_child->right_sibling, create_knode(2));
    set_right_sibling(k->root->left_child->right_sibling->left_child, create_knode(21));
    set_right_sibling(k->root->left_child->right_sibling->left_child->right_sibling, create_knode(49));
    set_left_child(k->root->left_child->right_sibling->left_child->right_sibling->right_sibling, create_knode(30));
    set_right_sibling(k->root->left_child->right_sibling->left_child->right_sibling->right_sibling->left_child, create_knode(72));
    set_right_sibling(k->root->left_child->right_sibling->left_child->right_sibling->right_sibling, create_knode(73));
    set_right_sibling(k->root->left_child->right_sibling, create_knode(4));
    set_left_child(k->root->left_child->right_sibling->right_sibling, create_knode(58));
    print_ktree(k);
}