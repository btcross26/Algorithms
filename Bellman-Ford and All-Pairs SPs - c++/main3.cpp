#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include "graph.h"

using namespace std;

void read_graph(Digraph &graph, string filename);
long find_shortest_distance(map<int, map<int, Digraph::wp_pair> > &apsps);

int main() {
    clock_t start, finish;
    Digraph::wp_pair ssp_pair;
    bool valid;
    
    // Calculate shortest shortest path for large graph
    Digraph digraph;
    cout << "Calculating shortest shortest path for large graph..." << endl;
    start = clock();
    read_graph(digraph, "large.txt");
    ssp_pair = Digraph::ss_path(digraph, valid);
    finish = clock();
    if(!valid) {
        cout << "Graph 1 contains negative cycles!" << endl;
    } else {
        cout << "Shortest shortest path distance: " << ssp_pair.distance << endl;
    }
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << " s" << endl << endl;
        
    return 0;
}

    
    
// read graph
void read_graph(Digraph &graph, string filename) {
    int head, tail, weight, num_nodes, num_edges;
    bool first_line = true;
    
    fstream input_file;    
    input_file.open(filename.c_str());
    
    // discard first line
    input_file >> num_nodes >> num_edges;
    
    while(input_file >> tail >> head >> weight) {
        graph.add_edge(tail, head, weight);        
    }
    input_file.close();
}


long find_shortest_distance(map<int, map<int, Digraph::wp_pair> > &apsps) {
    typedef map<int, map<int, Digraph::wp_pair> >::iterator iter1;
    typedef map<int, Digraph::wp_pair>::iterator iter2;
    long distance = ((((apsps.begin())->second).begin())->second).distance;
    
    for(iter1 it1 = apsps.begin(); it1 != apsps.end(); ++it1) {
        for(iter2 it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
            if((it2->second).distance < distance) distance = (it2->second).distance;
        }
    }
    
    return distance;
}
