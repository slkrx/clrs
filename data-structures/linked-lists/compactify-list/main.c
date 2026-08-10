#include <stdio.h>

int main() {
    int next[] = {2, 0, 3, -1, 5, 6, -1};
    int key[] = {2, 1, 3, 4, 0, 0, 0};
    int prev[] = {1, -1 , 0, 2, -1, 4, 5};
    int L = 1;
    int F = 4;

    int x = L, i = 0, x_key, i_key, x_next, i_next, x_prev, i_prev, temp_next, temp_key, temp_prev, j;
    while (x != -1) {
        if (x == i) {
            x = next[x];
            i++;
            continue;
        }
        if (F == i)
            F = x;
        else if (F == x)
            F = i;
        if (L == i)
            L = x;
        else if (L == x)
            L = i;

        i_next = next[i];
        i_key = key[i];
        i_prev = prev[i];
        x_next = next[x];
        x_key = key[x];
        x_prev = prev[x];

        if (i_next != -1)
            prev[i_next] = x;
        if (i_prev != -1)
            next[i_prev] = x;

        if (x_next != -1)
            prev[x_next] = i;
        if (x_prev != -1)
            next[prev[x]] = i;

        temp_next = next[i];
        temp_key = key[i];
        temp_prev = prev[i];

        next[i] = next[x];
        key[i] = key[x];
        prev[i] = prev[x];

        next[x] = temp_next;
        key[x] = temp_key;
        prev[x] = temp_prev;

        x = next[i];
        i++;
    for (j = 0; j < 7; j++)
        printf("%2d ", j);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", next[j]);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", key[j]);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", prev[j]);
    putchar('\n');
    putchar('\n');
    }

    for (j = 0; j < 7; j++)
        printf("%2d ", j);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", next[j]);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", key[j]);
    putchar('\n');
    for (j = 0; j < 7; j++)
        printf("%2d ", prev[j]);
    putchar('\n');
    printf("%d\n", L);
    printf("%d\n", F);
}