#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <ctime>
#include "txtfileio.h"
#include "union_find.h"

using namespace std;
using namespace txtfileio;

long read_nodes(map<unsigned long, unsigned long> &nodes);
void compute_clusters(Union_find<long> &components, map<unsigned long, unsigned long> &nodes);
vector<unsigned long> candidate_connections(unsigned long number);

int main() {
    clock_t start, finish;
    map<unsigned long, unsigned long> node_map;
    long num_nodes;
    
    // read nodes into node map
    cout << "\nReading text file and creating node map...." << endl;  
    start = clock();
    num_nodes = read_nodes(node_map);
    finish = clock();
    cout << "Time for node map creation: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;         
    cout << "Size of node map is: " << num_nodes << endl << endl;
     
    // compute clusters: final number of clusters is
    cout << "Computing clusters..." << endl;
    start = clock();
    Union_find<long> clusters(num_nodes);
    compute_clusters(clusters, node_map);
    finish = clock();
    cout << "Computation time: " << 1000.0 * (finish - start) / CLOCKS_PER_SEC
         << " ms" << endl;
    cout << "Number of clusters: " << clusters.count_components() << endl;
      
    return 0;
}



long read_nodes(map<unsigned long, unsigned long> &nodes) {
    vector<string> lines = readlines("clustering_big.txt"), tokens;
    typedef vector<string>::iterator iter;
    string binary_number = "";
    unsigned long number;
    long mapped_node_number = 1;
    
    for(int i = 1; i < lines.size(); i++) {
        tokenize(lines[i], tokens, " ", true);
        for(iter it = tokens.begin(); it != tokens.end(); ++it) {
            binary_number += (*it);
        }
        number = bitset<24>(binary_number).to_ulong();
        if(nodes.find(number) == nodes.end()) {
            nodes[number] = mapped_node_number;
            ++mapped_node_number;
        }
        binary_number = "";
        tokens.clear();
    }
    
    // return number of unique nodes by length of map
    return (long)nodes.size();
}


void compute_clusters(Union_find<long> &components, map<unsigned long, unsigned long> &nodes) {
    typedef map<unsigned long, unsigned long>::iterator iter_map;
    vector<unsigned long> candidates;
    typedef vector<unsigned long>::iterator iter_vec;
    long node1, node2;
    
    for(iter_map it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
        candidates = candidate_connections((*it1).first);
        node1 = nodes[(*it1).first];
        for(iter_vec it2 = candidates.begin(); it2 != candidates.end(); ++it2) {
            if(nodes.find((*it2)) != nodes.end()) {
                node2 = nodes[(*it2)];
                components.add_connection(node1, node2);
            }
        }
        candidates.clear();
    }
}

// return candidates as list of numbers that are within hamming distance of 2 from number
// note that nodes within distance zero (identical nodes) were eliminated during the mapping process
vector<unsigned long> candidate_connections(unsigned long number) {
    vector<unsigned long> candidates;
    bitset<24> binary_number(number), bn_copy;
    
    // candidates for hamming distance = 1 or 2
    for(int i = 0; i < 24; i++) {
        for(int j = i; j < 24; j++) {
            bn_copy = binary_number;
            bn_copy.flip(i);
            if(i != j) {
                bn_copy.flip(j);
            }
            candidates.push_back(bn_copy.to_ulong());
        }
    }
    return candidates;
}