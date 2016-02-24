#ifndef _DIGRAPH_H
#define _DIGRAPH_H

#include <unordered_map>
#include <vector>

class Digraph {
    public:
        struct Edge {
            int node1;
            int node2;
            Edge(int node1, int node2) : node1(node1), node2(node2) {}
        };
        
    private:
        std::unordered_map<int, std::vector<Edge*> > alist_f;
        std::unordered_map<int, std::vector<Edge*> > alist_b;
        std::vector<Edge*> edge_list;
        
    public:   // constructors and destructor
        Digraph();
        ~Digraph();
        
    public:   // instance methods
        void add_edge(int tail_node, int head_node);
        int num_nodes() { return this->alist_f.size(); }
        std::vector<int> scc_sizes();
        
    private:
        // make copy constructor and assignment illegal
        Digraph(const Digraph &digraph) {};
        Digraph &operator=(const Digraph &digraph) { return *this; }       
};

#endif