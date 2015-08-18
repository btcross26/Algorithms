#ifndef _DIGRAPH_H
#define _DIGRAPH_H

#include <unordered_map>
#include <vector>

class Digraph { 
    private:
        const int SIZE;
        std::vector<int> **alist;
        
    public:   // constructor and destructor
        Digraph(int size);
        ~Digraph();
        
    public:   // instance methods
        void add_edge(int tail_node, int head_node);
        int num_nodes() { return this->SIZE; }
        Digraph transpose() const;
        std::vector<int> scc_sizes();
        
    private:
        // make copying and assignment illegal
        Digraph(const Digraph &digraph) : SIZE(digraph.SIZE) {}
        Digraph &operator=(const Digraph &digraph) { return *this; }
};

#endif