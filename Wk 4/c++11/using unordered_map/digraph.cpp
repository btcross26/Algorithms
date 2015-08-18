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


// constructors
Digraph::Digraph() {}

Digraph::Digraph(const Digraph &digraph) : alist(digraph.alist) {}


// operator overloads
Digraph &Digraph::operator=(const Digraph &digraph) {
    this->alist = digraph.alist;
    return *this;
}


// public instance methods
void Digraph::add_edge(int tail_node, int head_node) {
    this->alist[tail_node].push_back(head_node);
    if(this->alist.find(head_node) == this->alist.end()) {
        this->alist[head_node];
    }
}

unordered_map<int, int> Digraph::dfs(int source_node) {
    // variable declarations
    unordered_map<int, int> dfs_finish;
    stack<int> to_explore;
    int finish = 1;

    // dfs search
    to_explore.push(source_node);
    dfs_finish[source_node] = 0;
    while(!to_explore.empty()) {
        stack<int>::size_type stack_size = to_explore.size();
        for(int &node : this->alist[to_explore.top()]) {
            if(dfs_finish.find(node) == dfs_finish.end()) {
                to_explore.push(node);
                dfs_finish[node] = 0;
            }
        }
        if(to_explore.size() == stack_size) {
            int finished_node = to_explore.top();
            to_explore.pop();
            dfs_finish[finished_node] = finish;
            ++finish;
        }
    }    
    return dfs_finish;  
}

Digraph Digraph::transpose() const {
    Digraph digraph;
    for(auto &kv : this->alist) {
        int head_node = kv.first;
        for(const int &tail_node : kv.second) {
            digraph.add_edge(tail_node, head_node);
        }
    }
    return digraph;    
}

vector<int> Digraph::scc_sizes() {
    stack<int> to_explore;
    unordered_set<int> dfs_finish;
    vector<int> loop_order(this->alist.size());
    int finish = 0;

    // perform dfs on all vertices of transposed graph
    Digraph t_digraph = this->transpose();
    for(auto &kv : t_digraph.alist) {
        if(dfs_finish.find(kv.first) == dfs_finish.end()) {
            to_explore.push(kv.first);
            dfs_finish.insert(kv.first);
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(int &node : t_digraph.alist[to_explore.top()]) {
                    if(dfs_finish.find(node) == dfs_finish.end()) {
                        to_explore.push(node);
                        dfs_finish.insert(node);
                    }
                }
                if(to_explore.size() == stack_size) {
                    loop_order[finish] = to_explore.top();
                    to_explore.pop();
                    ++finish;
                }
            }
        }
    }
       
    // perform dfs on graph with reverse loop order
    dfs_finish.clear();
    vector<int> scc_sizes;    
    for(int i = this->alist.size(); i > 0; --i) {
        if(dfs_finish.find(loop_order[i]) == dfs_finish.end()) {
            int component_size = 0;
            to_explore.push(loop_order[i]);
            dfs_finish.insert(loop_order[i]);
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(int &node : this->alist[to_explore.top()]) {
                    if(dfs_finish.find(node) == dfs_finish.end()) {
                        to_explore.push(node);
                        dfs_finish.insert(node);
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