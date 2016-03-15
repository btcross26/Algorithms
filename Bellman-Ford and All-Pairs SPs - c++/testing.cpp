#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <string>
#include "graph.h"

using namespace std;

void read_graph(Digraph &graph, string filename);

int main(int argc, char** argv) {
    clock_t start, finish;
    Digraph graph;

    cout << "Reading input graph..." << endl;
    start = clock();
    read_graph(graph, argv[1]);
    finish = clock();
    cout << "Running time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl;
    cout << "Number of nodes: " << graph.node_count() << endl;
    cout << "Number of edges: " << graph.edge_count() << endl << endl;
    
    int lines = 0;
    cout << "Printing 25 smallest edges..." << endl;
    start = clock();
    std::vector<Edge> edge_list = graph.get_edge_list();
    for(vector<Edge>::iterator it = edge_list.begin(); it != edge_list.end(); ++it) {
        cout << it->tail << " " << it->head << " " << it->weight << endl;
        ++lines;
        if(lines == 25) break;
    }
    finish = clock();
    cout << "Running time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl;
    cout << "Edge list size: " << edge_list.size() << endl << endl;
    
    cout << "Testing Digraph copy constructor..." << endl;
    start = clock();
    Digraph copy(graph);
    finish = clock();
    cout << "Test complete." << endl;
    cout << "Number of nodes: " << copy.node_count() << endl;
    cout << "Number of edges: " << copy.edge_count() << endl;
    cout << "Running Time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl << endl;
    
    cout << "Testing Digraph assignment operator..." << endl;
    start = clock();
    copy = graph;
    finish = clock();
    cout << "Test complete." << endl;
    cout << "Number of nodes: " << copy.node_count() << endl;
    cout << "Number of edges: " << copy.edge_count() << endl;
    cout << "Running Time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl << endl;
    
    cout << "Testing Bellman-Ford Algorithm..." << endl;
    start = clock();
    bool no_neg_cycles;
    map<int, Digraph::wp_pair> shortest_path_distances = Digraph::bellman_ford(1, graph, no_neg_cycles);
    finish = clock();
    cout << "Test complete." << endl;
    if(!no_neg_cycles) {
        cout << "Graph contains negative cycles!" << endl;
    }
    cout << "Shortest path to node 137: " << shortest_path_distances[137].distance << endl;
    cout << "Running Time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl << endl;
    
    cout << "Testing Dijkstra's Algorithm..." << endl;
    start = clock();
    shortest_path_distances = Digraph::dijkstra_alg(1, graph);
    finish = clock();
    cout << "Test complete." << endl;
    cout << "Shortest path to node 137: " << shortest_path_distances[137].distance << endl;
    cout << "Running Time: " << 1e3 * (finish - start) / CLOCKS_PER_SEC << " ms" << endl << endl;
    
    cout << "Testing Johnson's Algorithm..." << endl;
    start = clock();
    map<int, map<int, Digraph::wp_pair> > apsps;
    apsps = Digraph::johnson_alg(graph);
    finish = clock();
    cout << "Test complete." << endl;
    cout << "Shortest path to node 137: " << apsps[1][137].distance << endl;
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
