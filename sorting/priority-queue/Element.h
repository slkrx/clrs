#ifndef ELEMENT_H
#define ELEMENT_H

#include <utility>

template <typename T>
class Element {
    int key;
    T *value;

    public:

    Element(int key, T *value) {
        this->key = key;
        this->value = value;
    }

    Element(const Element &e) {
        key = e.getKey();
        value = e.getValuePtr();
    }

    friend void swap(Element& first, Element& second) {
        std::swap(first.key, second.key);
        std::swap(first.value, second.value);
    }

    int getKey() const {
        return key;
    }

    void setKey(int i) {
        key = i;
    }

    T *getValuePtr() const {
        return value;
    }

    T getValue() {
        return *value;
    }
};

#endif