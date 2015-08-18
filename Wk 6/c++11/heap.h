#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <algorithm>

template<typename T>
class Heap {
    protected:
        std::vector<T> heap_vector;
        int min_heap;
        
    public:
        Heap(bool is_min_heap = false);
        T pop();
        void push(T value);
        T pushpop(T value);
        int size();
        T top();
};

//// Heap Class definitions

// public instance methods
template<typename T>
Heap<T>::Heap(bool is_min_heap) {
    std::make_heap(this->heap_vector.begin(), this->heap_vector.end());
    this->min_heap = is_min_heap ? -1 : 1;
}

template<typename T>
T Heap<T>::pop() {
    std::pop_heap(this->heap_vector.begin(), this->heap_vector.end());
    T value = this->min_heap * this->heap_vector.back();
    this->heap_vector.pop_back();
    return value;
}

template<typename T>
void Heap<T>::push(T value) {
    this->heap_vector.push_back(this->min_heap * value);
    std::push_heap(this->heap_vector.begin(), this->heap_vector.end());
}

template<typename T>
T Heap<T>::pushpop(T value) {
    this->push(value);
    T new_value = this->pop();
    return new_value;
}

template<typename T>
int Heap<T>::size() { return this->heap_vector.size(); }

template<typename T>
T Heap<T>::top() {
    std::pop_heap(this->heap_vector.begin(), this->heap_vector.end());
    T value = this->min_heap * this->heap_vector.back();
    std::push_heap(this->heap_vector.begin(), this->heap_vector.end());
    return value;
}

#endif