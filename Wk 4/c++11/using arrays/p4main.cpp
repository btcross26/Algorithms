#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "digraph.h"

using namespace std;

void read_file(Digraph &digraph, char* filename);

int main(int argc, char**argv) {
    clock_t start, finish;
    double elapsed_time;
    
    // read digraph
    start = clock();
    Digraph digraph(875714);
    read_file(digraph, argv[1]);
    finish = clock();
    elapsed_time = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to read file: " << elapsed_time << " ms" << endl;
    cout << "Number of vertices: " << digraph.num_nodes() << endl << endl;
    
    // calculate strongly connected component sizes
    start = clock();
    vector<int> scc_sizes = digraph.scc_sizes();
    finish = clock();
    elapsed_time = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Calculation time: " << elapsed_time << " ms" << endl;
    
    // Print out answer
    int count = 0;
    cout << "Component sizes: ";
    for(int i = scc_sizes.size() - 1; i > -1; --i) {
        cout << scc_sizes[i] << " ";
        ++count;
        if(count == 5)
            break;
    }

    return 0;
}

void read_file(Digraph &digraph, char* filename) {
    ifstream input_file(filename);
    int tail, head;    
    while(input_file >> tail >> head) {
        digraph.add_edge(tail, head);
    }
    input_file.close();
}