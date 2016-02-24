#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include "digraph.h"

using namespace std;
using std::cout;
using std::endl;


// constructor and destructor
Digraph::Digraph(int size) : SIZE(size) {
    this->alist = new vector<int>*[SIZE];
    for(int i = 0; i < this->SIZE; ++i) {
        this->alist[i] = 0;
    }
}

Digraph::~Digraph() {
    for(int i = 0; i < this->SIZE; ++i) {
        if(this->alist[i] != 0) {
            vector<int> *old = this->alist[i];
            this->alist[i] = 0;
            delete old;
        }
    }
    delete[] this->alist;
}


// public instance methods
void Digraph::add_edge(int tail_node, int head_node) {
    if(this->alist[tail_node - 1] == 0) {
        this->alist[tail_node - 1] = new vector<int>;
    }
    if(this->alist[head_node - 1] == 0) {
        this->alist[head_node - 1] = new vector<int>;
    }
    (this->alist[tail_node - 1])->push_back(head_node);
}

Digraph Digraph::transpose() const {
    Digraph digraph(this->SIZE);
    for(int i = 0; i < this->SIZE; ++i) {
        int head_node = i + 1;
        for(const int &tail_node : *(this->alist[i])) {
            digraph.add_edge(tail_node, head_node);
        }
    }
    return digraph;    
}

vector<int> Digraph::scc_sizes() {
    stack<int> to_explore;
    vector<int> dfs_finish(this->SIZE);
    vector<int> loop_order;

    // perform dfs on all vertices of transposed graph
    Digraph t_digraph = this->transpose();
    for(int i = 0; i < t_digraph.SIZE; ++i) {
        if(dfs_finish[i] == 0) {
            to_explore.push(i + 1);
            dfs_finish[i] = 1;
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(int &node : *(t_digraph.alist[to_explore.top() - 1])) {
                    if(dfs_finish[node - 1] == 0) {
                        to_explore.push(node);
                        dfs_finish[node - 1] = 1;
                    }
                }
                if(to_explore.size() == stack_size) {
                    loop_order.push_back(to_explore.top());
                    to_explore.pop();
                }
            }
        }
    }
       
    // perform dfs on graph with reverse loop order
    std::fill(dfs_finish.begin(), dfs_finish.end(), 0);
    vector<int> scc_sizes;
    for(int i = this->SIZE - 1; i > -1; --i) {
        int cnode = loop_order[i];
        if(dfs_finish[cnode -1] == 0) {
            int component_size = 0;
            to_explore.push(cnode);
            dfs_finish[cnode - 1] = 1;
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(int &node : *(this->alist[to_explore.top() - 1])) {
                    if(dfs_finish[node - 1] == 0) {
                        to_explore.push(node);
                        dfs_finish[node - 1] = 1;
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