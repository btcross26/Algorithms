#ifndef _DIGRAPH_H
#define _DIGRAPH_H

#include <vector>

class Digraph {
    public:
        const int SIZE;
        
    public:
        struct Edge {
            int node1;
            int node2;
            Edge(int node1, int node2) : node1(node1), node2(node2) {}
        };
        
    private:
        std::vector<Edge*> ***alist;
        std::vector<Edge*> edge_list;
        
    public:   // constructors and destructor
        Digraph(int size);
        ~Digraph();
        
    public:   // instance methods
        void add_edge(int tail_node, int head_node);
        int num_nodes() { return this->SIZE; }
        std::vector<int> scc_sizes();
        
    private:
        // make copy constructor and assignment illegal
        Digraph(const Digraph &digraph) : SIZE(0) {};
        Digraph &operator=(const Digraph &digraph) { return *this; }       
};

#endif