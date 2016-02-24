#ifndef _GRAPH_H
#define _GRAPH_H

#include <set>
#include <vector>
#include <map>

// class Digraph definition
class Digraph {
    public:
        struct Edge {
            int head, tail;
            Edge(int head, int tail) : head(head), tail(tail) {}
        };
    
    public:
        Digraph() : num_nodes(0) {}
        Digraph(const Digraph &digraph);
        Digraph& operator=(const Digraph &rhs);
        void add_edge(int tail_node, int head_node);
        int node_count() const { return this->num_nodes; }
        int edge_count() const;
        std::vector<Edge> get_edge_list() const;
        Digraph transpose() const;
        std::map<int, int> depth_first_search() const;
        std::vector< std::vector<int> > kosaraju_sccs();
        
    private:
        int num_nodes;
        std::map<int, std::vector<int> > alist;
    
    public:
        typedef std::map<int, std::vector<int> >::const_iterator iterator;
        iterator begin() const { return (this->alist).begin(); }
        iterator end() const { return (this->alist).end(); }
};

#endif
