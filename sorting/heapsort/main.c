#include "../argtoarr.c"
#include <stdio.h>
#include <math.h>

struct heap {
    int *A, size, length;
};

int height(struct heap *h) {
    return (int) log2(h->size);
}

int width(struct heap *h) {
    return (int) pow(2, height(h));
}

void printHeap(struct heap *H) {
    int i, h, j, k, m;
    h = height(H);
    k = 0;

    for (i = 0; i <= h; i++) {
        for (j = 0; j < pow(2, h - i) - 1; j++)
            printf("  ");
        for (j = 0; k < H->size && j < pow(2, i); j++) {
            printf("%2d", H->A[k++]);
            for (m = 0; m < pow(2, h - i + 1) - 1; m++)
                printf("  ");
        }
        putchar('\n');
    }
    putchar('\n');
}

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * (i + 1);
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(struct heap *h, int i) {
    int l, r, largest;

    l = left(i);
    r = right(i);

    if (l < h->size && h->A[l] > h->A[i])
        largest =l;
    else
        largest = i;

    if (r < h->size && h->A[r] > h->A[largest])
        largest = r;

    if (largest != i) {
        swap(h->A + i, h->A + largest);
        maxHeapify(h, largest);
    }
}

void buildMaxHeap(struct heap *h) {
    int i;

    h->size = h->length;
    for (i = h->length / 2; i >= 0; i--)
        maxHeapify(h, i);
}

void _heapsort(struct heap *H) {
    int i;

    buildMaxHeap(H);

    printHeap(H);
    for (i = H->length - 1; i > 0; i--) {
        swap(H->A, H->A + i);
        printHeap(H);
        H->size = H->size - 1;
        maxHeapify(H, 0);
        printHeap(H);
    }
}

int main(int argc, char **argv) {
    int *A, n;
    struct heap *h;

    h = malloc(sizeof(struct heap));
    h->length = argc - 1;
    h->size = h->length;
    h->A = argtoarr(argc, argv);

    _heapsort(h);

    for (int i = 0; i < h->length; i++) {
        printf("%d%c", h->A[i], i == h->length - 1 ? '\n' : ' ');
    }

    return 0;
}
