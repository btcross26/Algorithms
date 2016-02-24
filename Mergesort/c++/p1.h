#ifndef _MERGE_SORT_H
#define _MERGE_SORT_H
    
#include <vector>
#include <algorithm>

class MergeSort {
    public:
        long long inversions;
        
    public:
        MergeSort() : inversions(0) {}
        void reset_inversions() { this->inversions = 0; }
        template<typename T> std::vector<T> operator()(const std::vector<T> &array, int left_ind=0, int right_ind=-1);
        
    private:
        template<typename T> std::vector<T> sort(const std::vector<T> & array, int left_ind, int right_ind);
        template<typename T> std::vector<T> merge(const std::vector<T> &left, const std::vector<T> &right);
};

template<typename T>
std::vector<T> MergeSort::operator()(const std::vector<T> &array, int left_ind, int right_ind) {
    if(right_ind == -1)
        right_ind = array.size() - 1;
    else if(right_ind < left_ind) {
        right_ind = left_ind - 1;
    }
    return this->sort(array, left_ind, right_ind);
}

template<typename T>
std::vector<T> MergeSort::sort(const std::vector<T> & array, int left_ind, int right_ind) {
    if(right_ind - left_ind == 0) {
        return std::vector<T>(array.begin() + left_ind, array.begin() + left_ind + 1);
    }
    else {
        int index = (left_ind + right_ind) / 2;        
        return this->merge(this->sort(array, left_ind, index),
                           this->sort(array, index+1, right_ind));
    }
}

template<typename T>
std::vector<T> MergeSort::merge(const std::vector<T> &left, const std::vector<T> &right) {
    int nl = left.size(), nr = right.size(), i = 0, j = 0, index = 0;
    std::vector<T> merged(nl + nr);
    while(i < nl && j < nr) {
        if(left[i] <= right[j]) {
            merged[index] = left[i];
            ++i;
        } else {
            merged[index] = right[j];
            this->inversions += nl - i;
            ++j;
        }
        ++index;
    }
    
    if(i == nl) {
        std::copy(right.begin() + j, right.end(), merged.begin() + index);
    } else if (j == nr) {
        std::copy(left.begin() + i, left.end(), merged.begin() + index);
    }

    return merged;
}

#endif