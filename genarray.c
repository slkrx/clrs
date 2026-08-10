#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n;
    n = atoi(argv[1]);
    while (n-- > 0)
        printf(
            "%d%c",
            // (rand() & ~((~0u) << 1) ? -1 : 1) * (rand() % 100 + 1),
            rand() % 100,
            // rand(),
            // (rand() % (99999 - 10000 + 1)) + 10000,
            n == 0 ? '\n' : ' '
        );
}