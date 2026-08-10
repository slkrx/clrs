// #include "hash_table.c"
#include "open_addressing.c"

int main() {
    // hash_table *t = create_hash_table(9);
    // hash_table_insert(t, 5);
    // hash_table_insert(t, 28);
    // hash_table_insert(t, 19);
    // hash_table_insert(t, 15);
    // hash_table_insert(t, 20);
    // hash_table_insert(t, 33);
    // hash_table_insert(t, 12);
    // hash_table_insert(t, 17);
    // hash_table_insert(t, 10);
    // print_hash_table(t);
    hash_table *t = create_hash_table(11);
    hash_table_insert(t, 10);
    hash_table_insert(t, 22);
    hash_table_insert(t, 31);
    hash_table_insert(t, 4);
    hash_table_insert(t, 15);
    hash_table_insert(t, 28);
    hash_table_insert(t, 17);
    hash_table_insert(t, 88);
    hash_table_insert(t, 59);
    print_hash_table(t);
    hash_table_delete(hash_table_search(t, 28));
    hash_table_delete(hash_table_search(t, 17));
    hash_table_insert(t, 26);
    print_hash_table(t);
}