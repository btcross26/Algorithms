#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <ctime>
#include "txtfileio.h"
#include "union_find.h"

using namespace std;
using namespace txtfileio;

long read_edges(priority_queue< vector<long> > &edge_list);
void compute_clusters(Union_find<long> &components, priority_queue< vector<long> > &edge_list, int k);

int main() {
    clock_t start, finish;
    priority_queue< vector<long> > edge_list;
    
    // read edges into edge list queue
    cout << "\nReading text file and creating edge list...." << endl;  
    start = clock();
    long nodes = read_edges(edge_list);
    finish = clock();
    cout << "Time for edge list creation: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;         
    cout << "Size of edge list is: " << edge_list.size() << endl << endl;
    
    // compute clusters
    cout << "Computing clusters..." << endl;
    start = clock();
    Union_find<long> clusters(nodes);
    compute_clusters(clusters, edge_list, 4);
    finish = clock();
    cout << "Computation time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;
    cout << "Number of clusters: " << clusters.count_components() << endl;
    cout << "Remaining edges in list: " << edge_list.size() << endl << endl;
              
 	// output final answer: 106
    long max_distance = 0;
    while(true) {
        if(!clusters.connected(edge_list.top()[1], edge_list.top()[2])) {
            max_distance = -1 * edge_list.top()[0];
            break;
        }
        edge_list.pop();
    }
 	cout << "Maximum distance: " << max_distance << endl;
      
    return 0;
}



long read_edges(priority_queue< vector<long> > &edge_list) {
    vector<string> lines = readlines("clustering1.txt"), tokens;
    vector<long> edge;
    
    for(int i = 1; i < lines.size(); i++) {
        tokenize(lines[i], tokens, " ", true);
        edge.push_back(-1 * atol(tokens[2].c_str()));    // weights negated for priority queue push
        edge.push_back(atol(tokens[0].c_str()));
        edge.push_back(atol(tokens[1].c_str()));
        edge_list.push(edge);        
        edge.clear();
        tokens.clear();
    }
    
    // return size from first line of file
    return atol(lines[0].c_str());
}


void compute_clusters(Union_find<long> &components, priority_queue< vector<long> > &edge_list, int k) {
    vector<long> edge;
    
    while(components.count_components() > k) {
        edge = edge_list.top();
        edge_list.pop();
        components.add_connection(edge[1], edge[2]);
    }
}