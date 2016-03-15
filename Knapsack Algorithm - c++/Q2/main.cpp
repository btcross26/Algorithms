#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include "knapsack.h"

using namespace std;

void read_file(map<int, vector<int> > &items, int &sack_size, int &num_items, int &max_weight);

int main() {
    clock_t start, finish;
    map<int, vector<int> > items;
    int sack_size, num_items, max_weight, solution;
    
    // read items into file
    start = clock();
    read_file(items, sack_size, num_items, max_weight);
    finish = clock();
    cout << "Number of items read: " << items.size() << endl;
    cout << "   Time to read file: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;
    
    // calculate answer: 1279 ms with sorting, 593 ms without
    start = clock();
    Knapsack<int> knapsack(items, sack_size);
    solution = knapsack.get_solution();
    finish = clock();
    cout << "    Solution: " << solution << endl;
    cout << "Running Time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;    
    return 0;
}



void read_file(map<int, vector<int> > &items, int &sack_size, int &num_items, int &max_weight) {
    int item_no = 1, value, weight;
    bool first_line = true;
    
    max_weight = 0;    
    ifstream input_file("knapsack_big.txt");
    while(input_file >> value >> weight) {
        if(first_line) {
            sack_size = value;
            num_items = weight;
            first_line = false;
            continue;
        }
        items[item_no].push_back(value);
        items[item_no].push_back(weight);
        ++item_no;
        if(max_weight < weight) {
            max_weight = weight;
        }
    }
    input_file.close();    
}