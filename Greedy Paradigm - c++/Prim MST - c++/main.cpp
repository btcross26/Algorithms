#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "txtfileio.h"
#include "graph.h"

using namespace std;
using namespace txtfileio;

void read_graph(map<long, vector<long> > &graph, map<long, vector<long> > &weights);

int main() {
    clock_t start, finish;
    map<long, vector<long> > alist, weights;
    
    // read graph into Graph object
    cout << "\nReading text file and creating graph object...." << endl;  
    start = clock();
    read_graph(alist, weights);
    Graph<long> graph(alist, weights);
    finish = clock();
    cout << "Time for object creation: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl << endl;
    
    // compute minimum spanning tree
    cout << "Computing minimum spanning tree..." << endl;
    start = clock();
    Graph<long> min_spanning_tree = graph.calculate_min_spanning_tree();
    finish = clock();
    cout << "Computation time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl << endl;
         
    // compute total cost
    cout << "Computing total cost of tree..." << endl;
    start = clock();
    long total_weight = min_spanning_tree.get_total_weight();
    finish = clock();
    cout << "Computation time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl << endl;
         
 	// output final answer
 	cout << "Total cost: " << total_weight << endl;
      
    return 0;
}

void read_graph(map<long, vector<long> > &graph, map<long, vector<long> > &weights) {
    vector<string> lines = readlines("edges.txt"), tokens;
    long node1, node2, weight;
    
    for(int i = 1; i < lines.size(); i++) {
        tokenize(lines[i], tokens, " ", true);
        node1 = atol(tokens[0].c_str());
        node2 = atol(tokens[1].c_str());
        weight = atol(tokens[2].c_str());
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
        weights[node1].push_back(weight);
        weights[node2].push_back(weight);
        tokens.clear();
    }
}