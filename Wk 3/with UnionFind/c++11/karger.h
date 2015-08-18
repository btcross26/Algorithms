#ifndef _KARGER_H
#define _KARGER_H

#include <vector>

class Uedge {
    public:
        int tail, head;
    
    public:
        Uedge(int tail, int head);
        Uedge(const Uedge &other);
        Uedge& operator=(const Uedge &other);
};

class KargerEdgeList {
    private:
        int num_nodes, rpos;
        std::vector<Uedge> edge_list;
        
        
    public:
        KargerEdgeList(const std::vector<Uedge> &edge_list);
        KargerEdgeList(const KargerEdgeList &other);
        KargerEdgeList& operator=(const KargerEdgeList &other);
        int min_cuts(int iterations);
        
    private:
        Uedge& random_edge();
        void reset_reg();
};

#endif