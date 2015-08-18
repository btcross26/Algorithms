#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <ctime>

using namespace std;

long two_sum(char *filename, int lower = -10000, int upper = 10000);

int main(int argc, char **argv) {
    // calculate answer: runtime 1.11s with O3 flag
    clock_t start, finish;
    start = clock();
    long answer = two_sum(argv[1]);
    finish = clock();
    cout << "Computation time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC
         << " seconds" << endl;
    cout << "Answer: " << answer << endl << endl;
    
    return 0;
}

// hash table based method
long two_sum(char *filename, int lower, int upper) {
    // read_file into heap and transfer to vector
    ifstream input_file(filename);
    long long value;
    long range = upper - lower;
    unordered_map<long, unordered_set<long long> > num_map(10000000);
    while(input_file >> value) {
        num_map[(value - lower) / range].insert(value - lower);
    }
    input_file.close();
    
    // find and return answer
    unordered_set<int> existing_sums;
    for(auto &kv : num_map) {
        if(kv.first <= 0 && num_map.find(-kv.first) != num_map.end()) {
            for(long long value1 : kv.second) {
                for(long long value2 : num_map[-kv.first]) {
                    if(value1 + value2 <= range && value1 + value2 >= 0) {
                        existing_sums.insert(value1 + value2);
                    }
                }
            }
        }
        if(kv.first <= 0 && num_map.find(-kv.first + 1) != num_map.end()) {
            for(long long value1 : kv.second) {
                for(long long value2 : num_map[-kv.first + 1]) {
                    if(value1 + value2 <= range && value1 + value2 >= 0) {
                        existing_sums.insert(value1 + value2);
                    }
                }
            }
        }
        if(kv.first == 1) {
            for(long long value1 : kv.second) {
                for(long long value2 : kv.second) {
                    if(value1 != value2 && value1 + value2 <= range && value1 + value2 >= 0) {
                        existing_sums.insert(value1 + value2);
                    }
                }
            }
        }
    }  
    return existing_sums.size();
}