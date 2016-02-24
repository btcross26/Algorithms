#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <fstream>
#include <ctime>

using namespace std;

long two_sum(char *filename, int lower = -10000, int upper = 10000);

int main(int argc, char **argv) {
    // calculate answer: runtime w/o O3 flag: 0.58s, w 03: 0.26s
    clock_t start, finish;
    start = clock();
    long answer = two_sum(argv[1]);
    finish = clock();
    cout << "Computation time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC
         << " seconds" << endl;
    cout << "Answer: " << answer << endl << endl;
    
    return 0;
}

// sorted vector based method
long two_sum(char *filename, int lower, int upper) {
    // read_file and transfer to vector
    ifstream input_file(filename);
    long long value; 
    vector<long long> num_list;
    while(input_file >> value) {
        num_list.push_back(value);
    }
    input_file.close();
    sort(num_list.begin(), num_list.end());        
    
    // find and return answer
    int min_index = 0;
    int max_index = num_list.size() - 1;
    unordered_set<int> existing_sums;
    while(max_index > min_index) {
        while(num_list[min_index] + num_list[max_index] > upper && max_index > min_index)
            --max_index;
        for(int i = max_index; i > min_index; --i)
            if(num_list[min_index] + num_list[i] < lower) {
                break;
            } else if(num_list[min_index] != num_list[i]) {
                existing_sums.insert(num_list[min_index] + num_list[i]);
            }
        ++min_index;
    }    
    return existing_sums.size();
}