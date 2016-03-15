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
    long temp;
    long *shortest_distance[3];
    fill(shortest_distance, shortest_distance + 3, (long *)0);
    map<int, map<int, Digraph::wp_pair> > apsps;
    bool valid;
    
    // Check g1.txt
    Digraph digraph;
    cout << "Calculating shortest paths for graph 1..." << endl;
    start = clock();
    read_graph(digraph, "g1.txt");
    apsps = Digraph::johnson_alg(digraph, valid);
    if(valid) {
        shortest_distance[0] = &find_shortest_distance(apsps);
    } else {
        cout << "Graph 1 contains negative cycles!" << endl;
    }
    finish = clock();
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << " s" << endl << endl;
    
    // Check g2.txt
    digraph = Digraph();
    cout << "Calculating shortest paths for graph 2..." << endl;
    start = clock();
    read_graph(digraph, "g2.txt");
    apsps = Digraph::johnson_alg(digraph, valid);
    if(valid) {
        shortest_distance[1] = &find_shortest_distance(apsps);
    } else {
        cout << "Graph 2 contains negative cycles!" << endl;
    }
    finish = clock();
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << " s" << endl << endl;
    
    // Check g3.txt
    digraph = Digraph();
    cout << "Calculating shortest paths for graph 3..." << endl;
    start = clock();
    read_graph(digraph, "g3.txt");
    apsps = Digraph::johnson_alg(digraph, valid);
    if(valid) {
        shortest_distance[1] = &find_shortest_distance(apsps);
    } else {
        cout << "Graph 3 contains negative cycles!" << endl;
    }
    finish = clock();
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << " s" << endl;


    // Print shortest distances: NULL, NULL, -19
    for(int i = 0; i < 3; ++i) {
        if(shortest_distance[i] == 0) {
            cout << "Graph " << i+1 << " Shortest Distance: NULL" << endl;
        } else {
            cout << "Graph " << i+1 << " Shortest Distance: " << *shortest_distance[i] << endl;
        }
    }
    cout << endl << endl;
        
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
