#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "p1.h"

using namespace std;

vector<int> readfile(char* filename);

int main(int argc, char** argv) {
    clock_t start, finish;
    double total_time = 0.0;
    
    // read file
    start = clock();
    vector<int> integer_array = readfile(argv[1]);
    finish = clock();
    total_time += (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to read file: " << total_time << " seconds" << endl << endl;
    
    // sort list
    start = clock();
    MergeSort merge_sort;
    merge_sort(integer_array);
    finish = clock();
    total_time += (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to sort list: " << (finish - start) / CLOCKS_PER_SEC << " seconds" << endl;
    cout << "Total processing time: " << total_time << " seconds" << endl << endl;
    
    // answer
    cout << "Number of inversions: " << merge_sort.inversions << endl << endl;

    return 0;
}

vector<int> readfile(char* filename) {
    vector<int> array;
    int value;
    ifstream input_file(filename);
    while(input_file >> value) {
        array.push_back(value);
    }
    input_file.close();
    return array;
}