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
Digraph::Digraph(int size) : SIZE(size) {
    this->alist = new vector<Digraph::Edge*>**[this->SIZE];
    for(int i = 0; i < this->SIZE; ++i) {
        this->alist[i] = new vector<Digraph::Edge*>*[2];
        this->alist[i][0] = new vector<Digraph::Edge*>;
        this->alist[i][1] = new vector<Digraph::Edge*>;
    }
}

Digraph::~Digraph() {
    for(int i = 0; i < this->SIZE; ++i) {
        delete this->alist[i][0];
        delete this->alist[i][1];
        delete[] this->alist[i];
    }
    delete[] this->alist;
    for(int i = 0; i < this->edge_list.size(); ++i) {
        delete this->edge_list[i];
        this->edge_list[i] = 0;
    }
}

// public instance methods
void Digraph::add_edge(int tail_node, int head_node) {
    Edge *edge = new Edge(tail_node, head_node);
    this->edge_list.push_back(edge);
    (this->alist[tail_node - 1][0])->push_back(edge);
    (this->alist[head_node - 1][1])->push_back(edge);
}

vector<int> Digraph::scc_sizes() {
    stack<int> to_explore;
    vector<int> dfs_finish(this->SIZE, 0);
    stack<int> loop_order;

    // perform dfs on all vertices of transposed graph
    for(int i = 0; i < this->SIZE; ++i) {
        if(dfs_finish[i] == 0) {
            to_explore.push(i + 1);
            dfs_finish[i] = 1;
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(Digraph::Edge *edge : *(this->alist[to_explore.top() - 1][1])) {
                    if(dfs_finish[edge->node1 - 1] == 0) {
                        to_explore.push(edge->node1);
                        dfs_finish[edge->node1 - 1] = 1;
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
    vector<int> scc_sizes;    
    while(!loop_order.empty()) {
        int cnode = loop_order.top();
        loop_order.pop();
        if(dfs_finish[cnode - 1] == 1) {
            int component_size = 0;
            to_explore.push(cnode);
            dfs_finish[cnode - 1] = 2;
            while(!to_explore.empty()) {
                stack<int>::size_type stack_size = to_explore.size();
                for(Digraph::Edge *edge : *(this->alist[to_explore.top() - 1][0])) {
                    if(dfs_finish[edge->node2 - 1] == 1) {
                        to_explore.push(edge->node2);
                        dfs_finish[edge->node2 - 1] = 2;
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