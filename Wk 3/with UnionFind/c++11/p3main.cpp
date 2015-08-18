#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "karger.h"

using namespace std;

vector<Uedge> read_file(char* filename);

int main(int argc, char** argv) {
    clock_t start, finish;
    double elapsed_time = 0.0;
    
    // read file and create edge list vector: 0 ms
    start = clock();
    vector<Uedge> edge_list = read_file(argv[1]);
    finish = clock();
    elapsed_time = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to read file: " << elapsed_time << " ms" << endl << endl;
    
    // run Karger Min Cuts algorithm
    int numiters = 10000;
    start = clock();
    KargerEdgeList k_edges(edge_list);
    int mincuts = k_edges.min_cuts(numiters);
    finish = clock();
    elapsed_time = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Number of iterations used: " << numiters << endl;
    cout << "Time to perform calculations: " << elapsed_time << " ms" << endl;
    cout << "Minimum cuts: " << mincuts << endl << endl;
    
    return 0;
}

vector<Uedge> read_file(char* filename) {
    vector<Uedge> edge_list;
    ifstream input_file(filename);
    string line;
    stringstream ss;
    int tail, head;
    while(getline(input_file, line)) {
        ss.str("");
        ss.clear();
        for(int i = 0; i < line.size(); ++i) {
            if(line[i] == '\t')
                line[i] = ' ';
        }
        ss << line;
        ss >> tail;
        while(ss >> head) {
            if(tail < head) {
                edge_list.push_back(Uedge(tail, head));
            }
        }
    }
    input_file.close();
    return edge_list;
}