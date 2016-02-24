#ifndef _GRAPHBASE_H
#define _GRAPHBASE_H

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <iterator>     // std::forward_iterator_tag

template<typename NodeType> class Node_iter;    // input iterator for nodes

template<typename NodeType>
class GraphBase {
    public:
        virtual void add_edge(int tail_node, int head_node, int weight) = 0;
        const NodeType& operator[](int node) const;
        int node_count() const;
        virtual int edge_count() const = 0;
        
    protected:
        std::map<int, NodeType*> graph;
        int num_nodes;
        
    protected:
        GraphBase() : num_nodes(0) {}
        GraphBase(const GraphBase& graph);
        virtual ~GraphBase() {}
           
    // class iterators: note the iterators must be dereferenced twice to obtain object
    public:
        typedef Node_iter<NodeType> node_iterator;
        
    public:
        node_iterator begin() const { return node_iterator(this, false); }
        node_iterator end() const { return node_iterator(this, true); }

    // input iterator friend class
    friend class Node_iter<NodeType>;
};

// GraphBase implementations
// public members      
template<typename NodeType>
const NodeType& GraphBase<NodeType>::operator[](int node) const {
    if((*this).graph.find(node) == (*this).graph.end()) {
        std::cerr << "Node key error: Node not found" << std::endl;
        exit(1);
    }
    NodeType* node_ptr = (*this).graph.find(node)->second;
    return *node_ptr;
}

template<typename NodeType>
int GraphBase<NodeType>::node_count() const {
    return (*this).num_nodes;
}



// Node iterator class definition/implementation
template<typename NodeType>
class Node_iter {
    public:
        typedef size_t size_type;
        typedef NodeType value_type;
        typedef std::ptrdiff_t difference_type;
        typedef NodeType* pointer;
        typedef NodeType& reference;
        typedef std::input_iterator_tag iterator_category;
        
    private:
        const GraphBase<NodeType> *graph;
        typename std::map<int, NodeType*>::const_iterator it;
    
    public:
        Node_iter(const GraphBase<NodeType> *graph, bool end)
        : graph(graph), it(graph->graph.begin()) {
            if(end) (*this).it = graph->graph.end();
        }
        
        Node_iter(GraphBase<NodeType> *graph, bool end)
        : graph(graph), it(graph->graph.begin()) {
            if(end) (*this).it = graph->graph.end();            
        }    
        
        Node_iter(const Node_iter &other, bool end)
        : graph(other), it(graph->graph.begin()) {
            if(end) (*this).it = graph->graph.end();
        }

        Node_iter& operator=(const Node_iter &rhs) {
            (*this).graph = rhs.graph;
            (*this).it = rhs.it;
            return *this;
        }
        
        bool operator==(const Node_iter &iter) {
            return (*this).it == iter.it;
        }
        
        bool operator!=(const Node_iter &iter) {
            return !((*this) == iter);
        }
        
        Node_iter& operator++() {
            ++(*this).it;
            return *this;
        }
        
        Node_iter operator++(int dummy) {
            Node_iter iter_copy = *this;
            ++(*this);
            return iter_copy;
        }
        
        const NodeType& operator*() {
            return *(it->second);
        }
        
        const NodeType* operator->() {
            const NodeType* node_ptr = it->second;
            return node_ptr;
        }
};

#endif
