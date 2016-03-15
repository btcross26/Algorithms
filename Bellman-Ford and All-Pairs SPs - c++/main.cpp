#include <iostream>
#include <fstream>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include "graph.h"

using namespace std;

void read_graph(Digraph &graph, string filename);
long APSP(const Digraph &digraph);

int main() {
    clock_t start, finish;
    long temp;
    long *shortest_distance[3];
    fill(shortest_distance, shortest_distance + 3, (long *)0);
    
    // Check g1.txt
    Digraph digraph;
    bool valid;
    cout << "Calculating shortest paths for graph 1..." << endl;
    start = clock();
    read_graph(digraph, "g1.txt");
    Digraph::bellman_ford(1, digraph, valid);
    if(valid) {
        temp = APSP(digraph);
        shortest_distance[0] = &temp;
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
    Digraph::bellman_ford(1, digraph, valid);
    if(valid) {
        temp = APSP(digraph);
        shortest_distance[1] = &temp;
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
    Digraph::bellman_ford(1, digraph, valid);
    if(valid) {
        temp = APSP(digraph);
        shortest_distance[2] = &temp;
    } else {
        cout << "Graph 3 contains negative cycles!" << endl;
    }
    finish = clock();
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC << " s" << endl << endl;


    // Print shortest distances
    for(int i = 0; i < 3; ++i) {
        if(shortest_distance[i] == 0) {
            cout << "Graph " << i+1 << " Shortest Distance: NULL" << endl;
        } else {
            cout << "Graph " << i+1 << " Shortest Distance: " << *shortest_distance[i] << endl;
        }
    }
    cout << endl;
    
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



// All Pairs Shortest Paths (APSP) brute-force using Bellman-Ford
long APSP(const Digraph &digraph) {
    long shortest_distance;
    bool valid;
    map<int, Digraph::wp_pair> answer;
    map<int, long> shortest_distances;
    
    cout << "Calculating shortest distances..." << endl;
    for(Digraph::node_iterator it1 = digraph.begin(); it1 != digraph.end(); ++it1) {
        answer = Digraph::bellman_ford(it1->get_id(), digraph, valid);
        shortest_distance = ((answer.begin())->second).distance;
        for(map<int, Digraph::wp_pair>::iterator it2 = answer.begin(); it2 != answer.end(); ++it2) {
            if((it2->second).distance < shortest_distance) {
                shortest_distance = (it2->second).distance;
            }
        }
        shortest_distances[it1->get_id()] = shortest_distance;
    }
    
    shortest_distance = (shortest_distances.begin())->second;
    for(map<int, long>::iterator it = shortest_distances.begin(); it != shortest_distances.end(); ++it) {
        if(it->second < shortest_distance) {
            shortest_distance = it->second;
        }
    }
    
    return shortest_distance;
}
