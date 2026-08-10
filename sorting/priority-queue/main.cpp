#include <iostream>
#include "Heap.h"

int main() {
    std::vector<int> values = { 27,17,3,16,13,10,1,5,7,12,4,8,9,0,22,54,33,67,42,-3 };
    std::vector<Element<int>> a;
    for(int i = 0; i < values.size(); i++)
        a.emplace_back(values[i], &values[i]);
    
    Heap<int> heap(a);
    heap.print();
    int *p = new int(83);
    heap.insert({*p, p});
    heap.print();
    std::cout << "\n";
}