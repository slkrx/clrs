#include "irbtree.c"

int main() {
    interval ints[] = {{26,26}, {8,9}, {25,30},{16,21}, {19,20}, {15,23}, {17,19}, {5,8}, {0,3}, {6,10}};
    irbtree *T = create_tree();
    for (int i = 0; i < sizeof(ints) / sizeof(interval); i++)
        insert(T, ints[i]);
    print_tree_visual(T);
    node *x;
    x = search(T, (interval) {11, 14});
    printf("[%d,%d]\n", x->i.low, x->i.high);
    x = search(T, (interval) {22, 25});
    printf("[%d,%d]\n", x->i.low, x->i.high);
    x = search(T, (interval) {15, 16});
    printf("[%d,%d]\n", x->i.low, x->i.high);
    x = open_search(T, (interval) {15, 16});
    printf("[%d,%d]\n", x->i.low, x->i.high);
    x = min_overlap(T, (interval) {8, 8});
    printf("[%d,%d]\n", x->i.low, x->i.high);
    putchar('\n');
    spanning_overlap(T, (interval) {8, 20});
    putchar('\n');
    x = exact_search(T, (interval) {15, 23});
    printf("[%d,%d]\n", x->i.low, x->i.high);
}