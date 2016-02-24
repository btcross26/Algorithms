#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <random>
#include "unionfind.h"
#include "karger.h"

using namespace std;

// random uniform distribution generator with default seed
minstd_rand0 g1;
uniform_real_distribution<double> ud(0.0, 1.0);

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
    unordered_set<int> nodes;
    for(Uedge &edge : this->edge_list) {
        nodes.insert(edge.tail);
        nodes.insert(edge.head);
    }
    this->num_nodes = nodes.size();
}

KargerEdgeList::KargerEdgeList(const KargerEdgeList &other) { this->edge_list = other.edge_list; }

KargerEdgeList& KargerEdgeList::operator=(const KargerEdgeList &other) {
    this->edge_list = other.edge_list;
    return *this;
}

int KargerEdgeList::min_cuts(int iterations) {
    int min_cuts = this->edge_list.size();
    for(int i = 0; i < iterations; ++i) {
        Unionfind clusters(this->num_nodes);
        this->reset_reg();
        while(clusters.get_num_clusters() > 2) {
            Uedge next_edge = this->random_edge();
            clusters.merge(next_edge.tail, next_edge.head);
        }
        int cuts = 0;
        for(int j = 0; j < this->rpos; ++j) {
            if(!clusters.is_connected(this->edge_list[j].head, this->edge_list[j].tail))
                ++cuts;
        }
        if(cuts < min_cuts) {
            min_cuts = cuts;
        }
    }
    return min_cuts;
}

Uedge& KargerEdgeList::random_edge() {
    int next = ud(g1) * this->rpos;
    --this->rpos;
    swap(this->edge_list[next], this->edge_list[rpos]);
    return this->edge_list[rpos];
}

void KargerEdgeList::reset_reg() { this->rpos = this->edge_list.size(); }