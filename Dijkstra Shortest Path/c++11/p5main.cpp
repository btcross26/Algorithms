#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <ctime>
#include "graph.h"

using namespace std;

template<typename T>
void read_file(Graph<T> &graph, char* filename);

int main(int argc, char** argv) {
    clock_t start, finish;
    double elapsed = 0.0;
    
    // read file into graph object and calculate shortest paths
    // 0 ms without optimization
    start = clock();
    Graph<int> graph;
    read_file(graph, argv[1]);
    unordered_map<int, int> distances = Graph<int>::shortest_paths(graph, 1);
    finish = clock();
    elapsed = 1000.0 * (finish - start) / CLOCKS_PER_SEC;
    cout << "Time to run program: " << elapsed << " ms" << endl;
    cout << "Graph vertex count: " << graph.num_vertices() << endl;
    cout << "Graph edge count: " << graph.num_edges() << endl << endl;
    
    // print answer
    int nodes[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
    cout << "Answer: ";
    for(int i = 0; i < 10; ++i) {
        if(distances.find(nodes[i]) == distances.end()) {
            cout << "1000000";
        } else {
            cout << distances[nodes[i]];
        }
        if(i < 9) {
            cout << ",";
        }
    }
    cout << endl;
    
    return 0;
}

template<typename T>
void read_file(Graph<T> &graph, char* filename) {
    ifstream input_file(filename);
    string line;
    while(getline(input_file, line)) {
        for(int i = 0; i < line.size(); ++i) {
            if(line[i] == '\t' || line[i] == ',') {
                line[i] = ' ';
            }
        }
        stringstream ss(line);
        int node1, node2;
        T weight;
        ss >> node1;
        while(ss >> node2 >> weight) {
            if(node1 < node2) {
                graph.add_edge(node1, node2, weight);
            }
        }
        line.clear();
        ss.str("");
        ss.clear();
    }
}

