#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "quicksort.h"

using namespace std;
using Quicksort::quicksort;
using Quicksort::comparisons;

template<typename T> void read_file(vector<T> &array, char* filename);

int main(int argc, char**argv) {
    clock_t start, finish;
    double time_elapsed = 0.0;
    
    // read file into array
    start = clock();
    vector<int> array;
    read_file(array, argv[1]);
    finish = clock();
    time_elapsed = 1.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to read file: " << time_elapsed << " seconds" << endl << endl;
    
    // make array copy and sort array for problem 1
    vector<int> array_copy = array;
    start = clock();
    quicksort(array_copy, 0, array.size() - 1, 1);
    finish = clock();
    time_elapsed = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time for sorting method 1: " << time_elapsed << " ms" << endl;
    cout << "Number of comparisons: " << comparisons << endl << endl;
    comparisons = 0;
       
    // make array copy and sort array for problem 2
    array_copy = array;
    start = clock();
    quicksort(array_copy, 0, array_copy.size() - 1, 2);
    finish = clock();
    time_elapsed = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time for sorting method 2: " << time_elapsed << " ms" << endl;
    cout << "Number of comparisons: " << comparisons << endl << endl;
    comparisons = 0;
    
    // make array copy and sort array for problem 3
    array_copy = array;
    start = clock();
    quicksort(array_copy, 0, array_copy.size() - 1, 3);
    finish = clock();
    time_elapsed = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time for sorting method 3: " << time_elapsed << " ms" << endl;
    cout << "Number of comparisons: " << comparisons << endl << endl;
    comparisons = 0;
    
    return 0;
}

template<typename T>
void read_file(vector<T> &array, char* filename) {
    ifstream input_file(filename);
    T value;
    while(input_file >> value)
        array.push_back(value);
    input_file.close();
}