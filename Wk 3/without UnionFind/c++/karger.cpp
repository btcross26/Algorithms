#include <iostream>
#include <vector>
#include <algorithm>
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

bool Uedge::self_loop(const Uedge &other) { return other.head == other.tail; }



// KargerEdgeList definitions
KargerEdgeList::KargerEdgeList(const std::vector<Uedge> edge_list) : edge_list(edge_list) {}

KargerEdgeList::KargerEdgeList(const KargerEdgeList &other) { this->edge_list = other.edge_list; }

KargerEdgeList& KargerEdgeList::operator=(const KargerEdgeList &other) {
    this->edge_list = other.edge_list;
    return *this;
}

int KargerEdgeList::min_cuts(int iterations) {
    typedef vector<Uedge>::iterator iter;    
    int min_cuts = this->edge_list.size(), cuts;
    for(int i = 0; i < iterations; ++i) {
        vector<Uedge> edges_copy = this->edge_list;
        random_shuffle(edges_copy.begin(), edges_copy.end());
        iter end = edges_copy.end();
        while(end != edges_copy.begin()) {
            cuts = end - edges_copy.begin();
            int tail = (edges_copy.begin())->tail;
            int head = (edges_copy.begin())->head;
            for(iter it = edges_copy.begin(); it < end; ++it) {
                if(it->head == head) {
                    it->head = tail;
                }
                if(it->tail == head) {
                    it->tail = tail;
                }
            }
            end = remove_if(edges_copy.begin(), end, Uedge::self_loop);
        }
        if(cuts < min_cuts)
            min_cuts = cuts;        
    }
    return min_cuts;
}