#include <iostream>
#include <fstream>
#include <ctime>
#include "heap.h"

using namespace std;

long long sum_of_streaming_medians(char *filename);

int main(int argc, char **argv) {
    // answer: runtime w/o O3 flag: <10 ms, with flag: <10ms
    clock_t start, finish;
    start = clock();
    long long sum = sum_of_streaming_medians(argv[1]);
    finish = clock();
    cout << "Computation time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;
    cout << "Answer: " << sum % 10000 << endl << endl;
    return 0;
}

long long sum_of_streaming_medians(char *filename) {
    ifstream input_file(filename);
    int value;
    long long sum = 0;
    Heap<int> min_heap(true);
    Heap<int> max_heap;
    while(input_file >> value) {
        if(min_heap.size() == max_heap.size()) {
            value = min_heap.pushpop(value);
            max_heap.push(value);
        } else {
            value = max_heap.pushpop(value);
            min_heap.push(value);
        }
        sum += max_heap.top();
    }
    cout << endl;
    return sum;
}

