#ifndef _DIGRAPH_H
#define _DIGRAPH_H

#include <unordered_map>
#include <vector>

class Digraph { 
    private:
        std::unordered_map<int, std::vector<int> > alist;
        
    public:   // constructors
        Digraph();
        Digraph(const Digraph &digraph);
        
    public:   // operator overloads
        Digraph &operator=(const Digraph &digraph);
        
    public:   // instance methods
        void add_edge(int tail_node, int head_node);
        std::unordered_map<int, int> dfs(int source_node);
        int num_nodes() { return this->alist.size(); }
        Digraph transpose() const;
        std::vector<int> scc_sizes();
};

#endif