#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include <vector>
#include <algorithm>

namespace Quicksort {    
    static long comparisons = 0;
    
    template<typename T>
    int pivot_index(const std::vector<T> &array, int left, int right, int method) {
        switch(method) {
            case 1:
            default:
                return left;
            case 2:
                return right;
            case 3: {
                int middle_index = (left + right) / 2;
                int values[3] = {left, middle_index, right};
                if(array[values[1]] < array[values[0]]) {
                    std::swap(values[0], values[1]);
                }
                if(array[values[2]] < array[values[1]]) {
                    std::swap(values[1], values[2]);
                }
                if(array[values[1]] < array[values[0]]) {
                    std::swap(values[0], values[1]);
                }
                return values[1];
            }
        }
    }
    
    // indexed version: right index argument should be equal to actual index
    template<typename T>
    void quicksort(std::vector<T> &array, int left, int right, int method = 1) {
        if(right - left < 1) {
            return;
        } else {
            comparisons += right - left;
            int pivot = pivot_index(array, left, right, method);
            T pivot_value = array[pivot];
            std::swap(array[pivot], array[left]);
            pivot = left;
            for(int i = left + 1; i <= right; ++i) {
                if(array[i] < pivot_value) {
                    std::swap(array[pivot+1], array[i]);
                    ++pivot;
                }
            }
            std::swap(array[left], array[pivot]);
            quicksort(array, left, pivot - 1, method);
            quicksort(array, pivot + 1, right, method);
        }
    }
}

#endif