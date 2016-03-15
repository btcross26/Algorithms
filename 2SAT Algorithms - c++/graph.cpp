#include <map>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <queue>
#include <stack>
#include <algorithm>
#include "graph.h"
#include <iostream>

// Digraph implementation
Digraph::Digraph(const Digraph &digraph) {
    this->num_nodes = digraph.num_nodes;
    this->alist = digraph.alist;
}

Digraph& Digraph::operator=(const Digraph &rhs) {
    this->num_nodes = rhs.num_nodes;
    this->alist = rhs.alist;
    return *this;
}

void Digraph::add_edge(int tail_node, int head_node) {
    // add new nodes if required
    if((this->alist).find(tail_node) == (this->alist).end()) {
        (*this).alist[tail_node] = std::vector<int>();
        ++(*this).num_nodes;
    }
    if((*this).alist.find(head_node) == (*this).alist.end()) {
        (*this).alist[head_node] = std::vector<int>();
        ++(*this).num_nodes;
    }
    (this->alist)[tail_node].push_back(head_node);
}

int Digraph::edge_count() const {
    int count = 0;
    for(Digraph::iterator it = this->begin(); it != this->end(); ++it) {
        count += (it->second).size();
    }
    return count;
}

std::vector<Digraph::Edge> Digraph::get_edge_list() const {       
    std::vector<Digraph::Edge> edge_list;
    
    for(Digraph::iterator it1 = this->begin(); it1 != this->end(); ++it1) {
        for(std::vector<int>::const_iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
            edge_list.push_back(Edge(it1->first, *it2));
        }
    }
    return edge_list;
}

Digraph Digraph::transpose() const {
    Digraph digraph;
    for(Digraph::iterator it1 = this->begin(); it1 != this->end(); ++it1) {
        for(std::vector<int>::const_iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2) {
            digraph.add_edge(*it2, it1->first);
        }
    }
    return digraph;
}

std::map<int, int> Digraph::depth_first_search() const {
    std::map<int, int> dfs_finish;
    std::stack<int> to_explore;
    std::stack<int>::size_type stack_size;
    int finish = 0, node;
    for(Digraph::iterator it1 = this->begin(); it1 != this->end(); ++it1) {
        node = it1->first;
        if(dfs_finish.find(node) == dfs_finish.end()) {
            to_explore.push(node);
            dfs_finish[node] = 0;
            while(!to_explore.empty()) {
                stack_size = to_explore.size();
                std::vector<int> const *nodes = &((this->alist.find(to_explore.top()))->second);
                for(std::vector<int>::const_iterator it2 = nodes->begin(); it2 != nodes->end(); ++it2) {
                    if(dfs_finish.find(*it2) == dfs_finish.end()) {
                        to_explore.push(*it2);
                        dfs_finish[*it2] = 0;
                    }
                }
                if(stack_size == to_explore.size()) {
                    node = to_explore.top();
                    ++finish;
                    dfs_finish[node] = finish;
                    to_explore.pop();
                }
            }
        }
    }
    return dfs_finish;
}


std::vector< std::vector<int> > Digraph::kosaraju_sccs() {
    // tranpose graph and perform depth first search
    std::map<int, int> t_finish = (this->transpose()).depth_first_search();
    
    // create loop order vector
    std::vector<int> loop_order(t_finish.size());
    for(std::map<int, int>::iterator it = t_finish.begin(); it != t_finish.end(); ++it) {
        loop_order[it->second - 1] = it->first;
    }
    std::reverse(loop_order.begin(), loop_order.end());
    
    // find strongly connected components
    std::map<int, int> sccs, finish;
    std::stack<int> to_explore;
    int component = 0;
    for(std::vector<int>::iterator it1 = loop_order.begin(); it1 != loop_order.end(); ++it1) {
        if(finish.find(*it1) == finish.end()) {
            ++component;
            to_explore.push(*it1);
            finish[*it1] = 0;
            while(!to_explore.empty()) {
                std::stack<int>::size_type stack_size = to_explore.size();
                std::vector<int> *nodes = &((this->alist.find(to_explore.top()))->second);
                for(std::vector<int>::const_iterator it2 = nodes->begin(); it2 != nodes->end(); ++it2) {
                    if(finish.find(*it2) == finish.end()) {
                        to_explore.push(*it2);
                        finish[*it2] = 0;                    
                    }
                }
                if(stack_size == to_explore.size()) {
                    sccs[to_explore.top()] = component;
                    to_explore.pop();
                }
            }
        }
    }
    
    std::vector< std::vector<int> > components(component);
    for(std::map<int, int>::iterator it = sccs.begin(); it != sccs.end(); ++it) {
        components[it->second - 1].push_back(it->first);
    }
    return components;
}
