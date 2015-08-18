#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <algorithm>
#include "digraph.h"

using namespace std;
using std::cout;
using std::endl;


// constructors and destructor
Digraph::Digraph() {}

Digraph::~Digraph() {
    this->alist_f.clear();
    this->alist_b.clear();
    for(int i = 0; i < this->edge_list.size(); ++i) {
        delete this->edge_list[i];
        edge_list[i] = 0;
    }
}

// public instance methods
void Digraph::add_edge(int tail_node, int head_node) {
    Edge *edge = new Edge(tail_node, head_node);
    this->edge_list.push_back(edge);
    this->alist_f[tail_node].push_back(edge);
    this->alist_b[head_node].push_back(edge);
    if(this->alist_f.find(head_node) == this->alist_f.end()) {
        this->alist_f[head_node];
    }
    if(this->alist_b.find(tail_node) == this->alist_b.end()) {
        this->alist_b[tail_node];
    }
}

vector<int> Digraph::scc_sizes() {
    stack<int> to_explore;
    unordered_set<int> dfs_finish;
    stack<int> loop_order;

    // perform dfs on all vertices of transposed graph
    for(auto &kv : this->alist_b) {
        if(dfs_finish.find(kv.first) == dfs_finish.end()) {
            to_explore.push(kv.first);
            dfs_finish.insert(kv.first);
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(Digraph::Edge *edge : this->alist_b[to_explore.top()]) {
                    if(dfs_finish.find(edge->node1) == dfs_finish.end()) {
                        to_explore.push(edge->node1);
                        dfs_finish.insert(edge->node1);
                    }
                }
                if(to_explore.size() == stack_size) {
                    loop_order.push(to_explore.top());
                    to_explore.pop();
                }
            }
        }
    }
       
    // perform dfs on graph with reverse loop order
    dfs_finish.clear();
    vector<int> scc_sizes;    
    while(!loop_order.empty()) {
        int cnode = loop_order.top();
        loop_order.pop();
        if(dfs_finish.find(cnode) == dfs_finish.end()) {
            int component_size = 0;
            to_explore.push(cnode);
            dfs_finish.insert(cnode);
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(Digraph::Edge *edge : this->alist_f[to_explore.top()]) {
                    if(dfs_finish.find(edge->node2) == dfs_finish.end()) {
                        to_explore.push(edge->node2);
                        dfs_finish.insert(edge->node2);
                    }
                }
                if(to_explore.size() == stack_size) {
                    to_explore.pop();
                    ++component_size;
                }
            }
            scc_sizes.push_back(component_size);
        }
    }
    sort(scc_sizes.begin(), scc_sizes.end());
    return scc_sizes;
}