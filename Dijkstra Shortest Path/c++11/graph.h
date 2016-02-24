#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

template<typename T>
class Graph {
    public:
        class Edge;
        
    private:
        std::unordered_map<int, std::vector<Edge*> > alist;
        std::vector<Edge*> edge_list;
        
    public:
        Graph();
        Graph(const Graph &other);
        ~Graph();
        Graph& operator=(const Graph&other);
        void print_out_edges(int node) const;
        void add_edge(int node1, int node2, T weight);
        int num_vertices() { return this->alist.size(); }
        int num_edges() { return this->edge_list.size(); }
        static std::unordered_map<int, T> shortest_paths(const Graph<T> &graph, int source_node);
};


// public typedefs
template<typename T>
class Graph<T>::Edge {
    public:
        int node1, node2;
        T weight;
        
    public:
        Edge(int node1, int node2, int weight)
        : node1(node1), node2(node2), weight(weight) {}
        
        Edge(const Edge &other)
        : node1(other.node1), node2(other.node2), weight(other.weight) {}
        
        Edge& operator=(const Edge &other) {
            this->node1 = other.node1;
            this->node2 = other.node2;
            this->weight = other.weight;
            return *this;
        }
        
        bool operator<(const Edge &other) const { return this->weight < other.weight; }
};


// constructors and destructor
template<typename T>
Graph<T>::Graph() {}

template<typename T>
Graph<T>::Graph(const Graph<T> &other) {
    for(Edge * const edge_ptr : other.edge_list) {
        Edge edge = *edge_ptr;
        this->add_edge(edge.node1, edge.node2, edge.weight);
    }
}

template<typename T>
Graph<T>::~Graph() {
    for(Edge *edge_ptr : this->edge_list) {
        Edge *old = edge_ptr;
        edge_ptr = 0;
        delete old;
    }
}

        
// operator overloads
template<typename T>
Graph<T>& Graph<T>::operator=(const Graph<T> &other) {
    this->alist.clear();
    for(Edge *edge_ptr : this->edge_list) {
        Edge *old = edge_ptr;
        edge_ptr = 0;
        delete old;
    }
    this->edge_list.clear();
    for(Edge * const edge_ptr : other.edge_list) {
        Edge edge = *edge_ptr;
        this->add_edge(edge.node1, edge.node2, edge.weight);
    }
    return *this;
}


// public instance methods
template<typename T>
void Graph<T>::print_out_edges(int node) const {
    if(this->alist.find(node) == this->alist.end()) {
        return;
    } else {
        std::vector<Edge*> out_edges = (this->alist.find(node))->second;
        if(out_edges.size() == 0) {
            std::cout << "Node " << node << " Out Edges: NA" << std::endl;
        } else {
            std::cout << "Node " << node << " Out Edges: ";
            for(Edge *edge_ptr : out_edges) {
                int out_node = edge_ptr->node1;
                if(out_node == node) {
                    out_node = edge_ptr->node2;
                }
                std::cout << "(" << out_node << ", " << edge_ptr->weight << ") ";            
            }
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Graph<T>::add_edge(int node1, int node2, T weight) {
    Edge *new_edge = new Edge(node1, node2, weight);
    this->alist[node1].push_back(new_edge);
    this->alist[node2].push_back(new_edge);
    this->edge_list.push_back(new_edge);
}
        
        
// public static methods
template<typename T>
std::unordered_map<int, T> Graph<T>::shortest_paths(const Graph<T>& graph, int source_node) {
    std::unordered_map<int, T> distances;
    std::priority_queue<Graph<T>::Edge> edges;
    distances[source_node] = 0;
    for(Edge * const edge_ptr : (graph.alist.find(source_node))->second) {
        if(edge_ptr->node1 == source_node) {
            edges.push(Edge(source_node, edge_ptr->node2, -edge_ptr->weight));
        } else {
            edges.push(Edge(source_node, edge_ptr->node1, -edge_ptr->weight));
        }
    }
    
    while(distances.size() < graph.alist.size() && !edges.empty()) {
        Edge next_edge = edges.top();
        edges.pop();
        if(distances.find(next_edge.node2) == distances.end()) {
            int next_node = next_edge.node2;
            distances[next_node] = -next_edge.weight;
            for(Edge * const edge_ptr : (graph.alist.find(next_node))->second) {
                int next_next_node = (edge_ptr->node1 == next_node) ? edge_ptr->node2 : edge_ptr->node1;
                if(distances.find(next_next_node) == distances.end()) {
                    edges.push(Edge(next_node, next_next_node, next_edge.weight - edge_ptr->weight));
                }
            }
        }
    }
    
    return distances;
}

#endif