#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "Element.h"
#include <math.h>
#include <iostream>
#include <cstdio>
#include <limits>

template <typename T>
class Heap
{
    std::vector<Element<T>> A;
    int length, size;

    public:

    Heap(std::vector<Element<T>> A) {
        this->A = A;
        length = A.size();
        size = A.size();
        buildmaxheap();
    }

    int height() {
        return (int) std::log2(size);
    }

    void print() {
        int i, j, k, m;
        k = 0;

        for (i = 0; i <= height(); i++) {
            for (j = 0; j < std::pow(2, height() - i) - 1; j++)
                std::cout << "  ";
            for (j = 0; k < size && j < std::pow(2, i); j++) {
                std::printf("%2d", A[k++].getValue());
                for (m = 0; m < std::pow(2, height() - i + 1) - 1; m++)
                    std::cout << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
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

    void max_heapify(int i) {
        int l, r, largest;

        l = left(i);
        r = right(i);

        if (l < size && A[l].getKey() > A[i].getKey())
            largest = l;
        else
            largest = i;

        if (r < size && A[r].getKey() > A[largest].getKey())
            largest = r;

        if (largest != i) {
            std::swap(A[i], A[largest]);
            max_heapify(largest);
        }
    }

    void buildmaxheap() {
        int i;

        size = length;
        for (i = length / 2; i >= 0; i--)
            max_heapify(i);
    }

    void sort() {
        for (int i = length - 1; i > 0; i--) {
            std::swap(A[0], A[i]);
            size--;
            max_heapify(0);
        }
        size = length;
    }

    T *maximum() {
        return A[1].getValuePtr();
    }

    T *extract_max() {
        if (size < 1) {
            std::cerr << "heap underflow";
            std::exit(1);
        }

        T *max = A[0].getValuePtr();
        A[0] = A[size - 1];
        size--;
        max_heapify(0);
        return max;
    }

    void increase_key(int i, int key) {
        if (key < A[i].getKey()) {
            std::cerr << "new key is smaller than current key";
            return;
        }
        A[i].setKey(key);
        while (i > 0 && A[parent(i)].getKey() < A[i].getKey()) {
            std::swap(A[i], A[parent(i)]);
            i = parent(i);
        }
    }

    void insert(Element<T> elt) {
        if (size == A.size())
            A.emplace_back(elt.getKey(), elt.getValuePtr());
        else 
            A[size] = elt;
        int key = elt.getKey();
        A[size].setKey(std::numeric_limits<int>::min());
        size++;
        increase_key(size - 1, key);
    }

};

#endif //HEAP_H