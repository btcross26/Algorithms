#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "unionfind.h"
#include "karger.h"

using namespace std;

// Uedge definitions
Uedge::Uedge(int tail, int head) : tail(tail), head(head) {}

Uedge::Uedge(const Uedge &other) {
    this->tail = other.tail;
    this->head = other.head;
}

Uedge& Uedge::operator=(const Uedge &other) {
    this->tail = other.tail;
    this->head = other.head;
    return *this;
}



// KargerEdgeList definitions
KargerEdgeList::KargerEdgeList(const std::vector<Uedge> &edge_list) : edge_list(edge_list) {
    set<int> nodes;
    typedef vector<Uedge>::const_iterator iter;
    for(iter it = edge_list.begin(); it != edge_list.end(); ++it) {
        nodes.insert(it->tail);
        nodes.insert(it->head);
    }
    this->num_nodes = nodes.size();
}

KargerEdgeList::KargerEdgeList(const KargerEdgeList &other) { this->edge_list = other.edge_list; }

KargerEdgeList& KargerEdgeList::operator=(const KargerEdgeList &other) {
    this->edge_list = other.edge_list;
    return *this;
}

int KargerEdgeList::min_cuts(int iterations) {
    typedef vector<Uedge>::iterator iter;    
    int min_cuts = this->edge_list.size();
    for(int i = 0; i < iterations; ++i) {
        random_shuffle(this->edge_list.begin(), this->edge_list.end());
        Unionfind clusters(this->num_nodes);
        for(iter it = this->edge_list.begin(); it != this->edge_list.end(); ++it) {
            clusters.merge(it->tail, it->head);
            if(clusters.get_num_clusters() == 2) {
                break;
            }
        }
        set<int> first_cluster = clusters.get_first_cluster();
        int cuts = 0;
        for(iter it = this->edge_list.begin(); it != this->edge_list.end(); ++it) {
            bool bit1 = first_cluster.find(it->tail) != first_cluster.end();
            bool bit2 = first_cluster.find(it->head) != first_cluster.end();
            cuts += (bit1 ^ bit2) ? 1 : 0;
        }
        if(cuts < min_cuts) {
            min_cuts = cuts;
        }
    }
    return min_cuts;
}