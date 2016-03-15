#ifndef _GRAPH_H
#define _GRAPH_H

#include <set>
#include <vector>
#include "graphbase.h"

// Edge class definition
class Edge {
    public:
        int tail, head, weight;
        
    public:
        Edge() {}
        Edge(int tail, int head, int weight);
        Edge(const Edge &other);
        Edge& operator=(const Edge &rhs);
        bool operator==(const Edge &other) const;
        bool operator!=(const Edge &other) const;       
        bool operator<(const Edge &other) const;
        
        class edge_sort_by_wt {
            public:
                bool operator()(const Edge &edge1, const Edge &edge2);
        };
};



// class SNode definition - simple graph node (allows no parallel edges)
class SNode {        
    public:
        SNode(int id, int weight);        
        int get_id() const;        
        bool has_out_node(int node) const;
        
    private:
        int id, weight;
        std::set<Edge> out_edges;
    
    friend class Ugraph;
    friend class Digraph;
};



// class Ugraph - Undirected graph definition
class Ugraph : public GraphBase<SNode> {
    public:
        Ugraph() : GraphBase<SNode>() {}
        Ugraph(const Ugraph &ugraph);
        Ugraph& operator=(const Ugraph &rhs);
        ~Ugraph();   
        void add_edge(int tail_node, int head_node, int weight = 1);
        int edge_count() const;
        std::vector<Edge> get_edge_list() const;
};



// class Digraph definition
class Digraph : public GraphBase<SNode> {
    public:
        class wp_pair {
            public:
                long distance;
                int pnode;
                
            public:
                wp_pair() : distance(0), pnode(0) {}
                wp_pair(long dist, int pn) : distance(dist), pnode(pn) {}
                bool operator==(const wp_pair &other) const {
                    return (*this).distance == other.distance && (*this).pnode == other.pnode;
                }
        };
        
    public:
        Digraph() : GraphBase<SNode>() {}
        Digraph(const Digraph &digraph);
        Digraph& operator=(const Digraph &rhs);
        ~Digraph(); 
        void add_edge(int tail_node, int head_node, int weight = 1);
        int edge_count() const;
        std::vector<Edge> get_edge_list() const;
        static std::map<int, Digraph::wp_pair> bellman_ford(int source, const Digraph &digraph, bool &valid);
        static std::map<int, Digraph::wp_pair> dijkstra_alg(int source, const Digraph &digraph);
        static std::map<int, std::map<int, Digraph::wp_pair> > johnson_alg(const Digraph &digraph, bool &valid);
        static Digraph::wp_pair ss_path(const Digraph &digraph, bool &valid);
        // static Digraph transpose();
};

#endif
