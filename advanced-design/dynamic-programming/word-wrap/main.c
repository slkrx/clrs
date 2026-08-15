#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "word-wrap.c"
#include "math.h"

void copy_word(char *source, char *target, int pos) {
    int i;

    for (i = 0; source[i] != '\0'; i++)
        target[pos + i] = source[i];
}

void wrap_words(int n, int *L, int M, char **target, char **words) {
    int x, y, i;
    y = 0;
    x = 0;

    for (i = 0; i < n; i++) {
        if (L[i] > M - x) {
            while (x < M) {
                target[y][x] = ' ';
                x++;
            }
            target[y][x] = '\0';
            y++;
            x = 0;
        }
        if (L[i] <= M - x) {
            copy_word(words[i], target[y], x);
            if (L[i] == M - x) {
                target[y][M] = '\0';
                y++;
                x = 0;
            } else {
                x += L[i];
                target[y][x] = ' ';
                x++;
            }
        }
    }
}

int main() {
    // char *words[] = { "The", "first", "part,", "The", "Fellowship", "of", "the", "Ring,", "told", "how", "Gandalf", "the", "Grey", "discovered", "that", "the", "ring", "possessed", "by", "Frodo", "and", "the", "Hobbit", "was", "in", "fact", "the", "One", "Ring,", "ruler", "of", "all", "the", "Rings", "of", "Power.", "It", "recounted", "the", "flight", "of", "Frodo", "and", "his", "companions", "from", "the", "quiet", "Shire", "of", "their", "home,", "pursued", "by", "the", "terror", "of", "the", "Black", "Riders", "of", "Mordor,", "until", "at", "last,", "with", "the", "aid", "of", "Aragorn", "the", "Ranger", "of", "Eriador,", "they", "came", "through", "desperate", "perils", "to", "the", "House", "of", "Elrond", "in", "Rivendell" };
    char *words[] = { "Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur", "adipiscing", "elit.", "Fusce", "faucibus,", "justo", "in", "molestie", "dictum,", "urna", "leo", "ultrices", "urna,", "a", "facilisis", "diam", "lacus", "ullamcorper", "velit.", "Donec", "felis", "ipsum,", "finibus", "id", "tortor", "et,", "venenatis", "convallis", "leo.", "Pellentesque", "ac", "lacus", "arcu.", "Donec", "mauris", "mi,", "efficitur", "quis", "sem", "et,", "dapibus", "lobortis", "erat.", "Praesent", "semper", "sit", "amet", "odio", "in", "posuere.", "Vivamus", "nec", "mollis", "sapien.", "Sed", "lacinia", "consectetur", "tortor", "a", "commodo.", "Aliquam", "rutrum", "justo", "sit", "amet", "neque", "molestie", "ultrices.", "Donec", "sit", "amet", "consequat", "nunc.", "Cras", "convallis", "molestie", "nulla", "bibendum", "semper.", "Quisque", "congue", "metus", "ac", "est", "tincidunt,", "ut", "auctor", "lorem", "viverra.", "Nam", "pretium", "felis", "at", "ex", "iaculis,", "nec", "efficitur", "lacus", "vulputate.", "Morbi", "ut", "pellentesque", "lorem,", "quis", "blandit", "sapien.", "Nam", "a", "ante", "iaculis,", "vulputate", "est", "quis,", "volutpat", "libero.", "Praesent", "ac", "tortor", "vitae", "nunc", "faucibus", "placerat.", "Maecenas", "in", "lectus", "nec", "libero", "scelerisque", "vestibulum.", "Nam", "interdum", "lorem", "sit", "amet", "dictum", "placerat.", "Mauris", "auctor", "ante", "neque,", "eu", "pretium", "nulla", "lacinia", "sed.", "Nullam", "et", "luctus", "nunc.", "Maecenas", "facilisis", "porta", "erat,", "vitae", "lacinia", "odio", "consequat", "ut.", "Integer", "tempus", "interdum", "sapien", "sed", "pharetra.", "Maecenas", "quis", "vehicula", "nisi.", "Aliquam", "erat", "volutpat.", "", "Phasellus", "a", "lacus", "erat.", "Sed", "lobortis", "fermentum", "eros", "ac", "eleifend.", "Vivamus", "blandit", "tempor", "metus,", "non", "finibus", "mi", "ultrices", "ac.", "Suspendisse", "molestie", "vestibulum", "cursus.", "Proin", "molestie", "nec", "tellus", "vel", "varius.", "Curabitur", "a", "ex", "eget", "orci", "molestie", "dignissim", "vitae", "vitae", "neque.", "Sed", "tempor", "mauris", "blandit,", "laoreet", "lacus", "quis,", "rutrum", "ipsum.", "Aliquam", "erat", "volutpat.", "Aliquam", "et", "justo", "sodales,", "lobortis", "eros", "in,", "tristique", "libero.", "Nam", "ullamcorper", "sed", "ex", "vel", "suscipit.", "Duis", "eleifend", "pellentesque", "elementum.", "Etiam", "nec", "nulla", "eget", "ligula", "mattis", "aliquet.", "Donec", "sollicitudin", "velit", "massa,", "auctor", "euismod", "nisi", "maximus", "ac.", "Duis", "pretium", "tincidunt", "nunc", "ut", "fringilla.", "", "Quisque", "gravida", "felis", "nec", "ligula", "ultrices,", "eget", "pretium", "augue", "euismod.", "Pellentesque", "in", "semper", "tortor.", "Nulla", "lacus", "odio,", "laoreet", "vitae", "bibendum", "sit", "amet,", "maximus", "et", "lectus.", "Sed", "imperdiet", "enim", "in", "nunc", "pharetra", "sollicitudin.", "Ut", "sapien", "neque,", "blandit", "ut", "leo", "sit", "amet,", "mollis", "ultricies", "nulla.", "Pellentesque", "rhoncus", "quam", "vitae", "ultricies", "facilisis.", "Aenean", "nulla", "nisl,", "faucibus", "quis", "luctus", "rutrum,", "suscipit", "a", "quam.", "Aenean", "nulla", "arcu,", "bibendum", "sed", "mauris", "eu,", "convallis", "varius", "libero.", "", "In", "quis", "euismod", "leo,", "non", "finibus", "nibh.", "Morbi", "finibus", "id", "nisi", "et", "aliquet.", "Duis", "consectetur", "molestie", "quam,", "ac", "tempus", "nisl", "viverra", "malesuada.", "Etiam", "egestas", "elementum", "felis,", "in", "blandit", "velit", "tristique", "nec.", "Curabitur", "lorem", "elit,", "suscipit", "ut", "ultricies", "in,", "lacinia", "non", "elit.", "Phasellus", "ut", "eros", "accumsan,", "rutrum", "sem", "eget,", "aliquam", "massa.", "In", "dictum,", "ante", "vel", "tempor", "ultricies,", "risus", "libero", "suscipit", "mi,", "a", "molestie", "odio", "dolor", "non", "eros.", "Vestibulum", "volutpat,", "felis", "ac", "ultrices", "venenatis,", "justo", "erat", "feugiat", "diam,", "vitae", "viverra", "elit", "nibh", "vitae", "lacus.", "Cras", "et", "nisi", "quis", "ex", "tincidunt", "ultricies.", "Fusce", "vitae", "pellentesque", "tellus." };

    // char *words[] = {"cat", "is", "an", "animal"};

    int n = sizeof(words)/sizeof(char*);
    int L[n];
    int i, j, M, m, k, x, y, N;

    for (i = 0; i < n; i++) {
        for (j = 0; words[i][j] != '\0'; j++);
        L[i] = j;
    }
    // M = 6;
    M = 150;
    N = 200;
    char *target[N];
    for (i = 0; i < N; i++) {
        target[i] = (char*) malloc(sizeof(char) * (M+1));
        target[i][0] = '\0';
    }
    
    wrap_words(n, L, M, target, words);

    for (i = 0; i < N; i++)
        if (target[i][0] == '\0')
            N = i;

    int sum = 0;
    int inner_sum = 0;
    for (i = 0; i < N; i++) {
        printf("%s\n", target[i]);
        inner_sum = 0;
        if (i < N - 1)
            for (j = M - 1; target[i][j] == ' '; j--)
                inner_sum++;
        sum += (int) pow(inner_sum, 3);
    }
    printf("%d\n", sum);
    solution s = word_wrap(n, L, M);
    putchar('\n');
    printf("%d\n", (int) s.c[n-1]);
    print_solution(words, s.b, n);
}
