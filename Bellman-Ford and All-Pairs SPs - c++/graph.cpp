#include <map>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <queue>
#include <algorithm>
#include "graph.h"

// Edge implementation
Edge::Edge(int tail, int head, int weight)
: tail(tail), head(head), weight(weight) {}

Edge::Edge(const Edge &other) {
    (*this).tail = other.tail;
    (*this).head = other.head;
    (*this).weight = other.weight;
}
        
Edge& Edge::operator=(const Edge &rhs) {
    (*this).tail = rhs.tail;
    (*this).head = rhs.head;
    (*this).weight = rhs.weight;
    return *this;
}
        
bool Edge::operator==(const Edge &other) const {
    return (*this).tail == other.tail && (*this).head == other.head;
}

bool Edge::operator!=(const Edge &other) const {
    return !(*this == other);
}
        
bool Edge::operator<(const Edge &other) const {
    return (*this).head < other.head || (*this).tail < other.tail; 
}
        
bool Edge::edge_sort_by_wt::operator()(const Edge &edge1, const Edge &edge2) {
    return edge1 != edge2 && edge1.weight < edge2.weight;
}




// class SNode implementation
SNode::SNode(int id, int weight) : id(id), weight(weight) {}
        
int SNode::get_id() const { return (*this).id; }
        
bool SNode::has_out_node(int node) const {
    Edge edge((*this).id, node, 1);
    return !((*this).out_edges.find(edge) == (*this).out_edges.end());
}




// Ugraph implementation
Ugraph::Ugraph(const Ugraph &ugraph) : GraphBase<SNode>() {
    (*this).num_nodes = ugraph.num_nodes;
    for(Ugraph::node_iterator it = ugraph.begin(); it != ugraph.end(); ++it) {
        (*this).graph[it->get_id()] = new SNode(*it);
    }
}

Ugraph& Ugraph::operator=(const Ugraph &rhs) {
    (*this).num_nodes = rhs.num_nodes;
    
    // delete any old pointers in graph map
    SNode* old_ptr;
    for(std::map<int, SNode*>::iterator it = (*this).graph.begin(); it != (*this).graph.end(); ++it) {
        old_ptr = it->second;
        (*this).graph.erase(it);
        delete old_ptr;
    }
    
    // add new node pointers into graph map
    for(Ugraph::node_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        (*this).graph[it->get_id()] = new SNode(*it);
    }
    
    return *this;
}

Ugraph::~Ugraph() {
    typedef std::map<int, SNode*>::iterator iter;
    SNode *old_node;
    
    // Delete nodes
    for(iter it = (*this).graph.begin(); it != (*this).graph.end(); ++it) {
        old_node = it->second;
        it->second = 0;
        delete old_node;
    }
}

void Ugraph::add_edge(int tail_node, int head_node, int weight) {    
    // add new nodes if required
    if((*this).graph.find(tail_node) == (*this).graph.end()) {
        (*this).graph[tail_node] = new SNode(tail_node, 1);
        ++(*this).num_nodes;
    }
    if((*this).graph.find(head_node) == (*this).graph.end()) {
        (*this).graph[head_node] = new SNode(head_node, 1);
        ++(*this).num_nodes;
    }
    
    (*this).graph[tail_node]->out_edges.insert(Edge(tail_node, head_node, weight));
    (*this).graph[head_node]->out_edges.insert(Edge(head_node, tail_node, weight));    
}

int Ugraph::edge_count() const {
    int count = 0;
    for(GraphBase<SNode>::node_iterator it = (*this).begin(); it != (*this).end(); ++it) {
        count += it->out_edges.size();
    }
    return count / 2;   // each edge stored twice in adjacency list for a Ugraph
}

std::vector<Edge> Ugraph::get_edge_list() const {
    std::set<Edge> edges;  
    for(GraphBase<SNode>::node_iterator it1 = (*this).begin(); it1 != (*this).end(); ++it1) {
        for(std::set<Edge>::iterator it2 = it1->out_edges.begin(); it2 != it1->out_edges.end(); ++it2) {
            if(it2->tail > it2->head) {
                edges.insert(Edge(it2->head, it2->tail, it2->weight));
            } else {
                edges.insert(*it2);
            }
        }
    }
    
    std::vector<Edge> edge_list(edges.begin(), edges.end());
    std::sort(edge_list.begin(), edge_list.end(), Edge::edge_sort_by_wt());
    return edge_list;
}




// Digraph implementation
Digraph::Digraph(const Digraph &digraph) : GraphBase<SNode>() {
    (*this).num_nodes = digraph.num_nodes;
    for(Digraph::node_iterator it = digraph.begin(); it != digraph.end(); ++it) {
        (*this).graph[it->get_id()] = new SNode(*it);
    }
}

Digraph& Digraph::operator=(const Digraph &rhs) {
    (*this).num_nodes = rhs.num_nodes;
    
    // delete any old pointers in graph map
    SNode* old_ptr;
    for(std::map<int, SNode*>::iterator it = (*this).graph.begin(); it != (*this).graph.end(); ++it) {
        old_ptr = it->second;
        (*this).graph.erase(it);
        delete old_ptr;
    }
    
    // add new node pointers into graph map
    for(Digraph::node_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        (*this).graph[it->get_id()] = new SNode(*it);
    }
    
    return *this;
}

Digraph::~Digraph() {
    typedef std::map<int, SNode*>::iterator iter_map;
    SNode *old_node;
    
    // Delete nodes
    for(iter_map it1 = (*this).graph.begin(); it1 != (*this).graph.end(); ++it1) {
        old_node = it1->second;
        it1->second = 0;
        delete old_node;
    }
}

void Digraph::add_edge(int tail_node, int head_node, int weight) {
    // add new nodes if required
    if((*this).graph.find(tail_node) == (*this).graph.end()) {
        (*this).graph[tail_node] = new SNode(tail_node, 1);
        ++(*this).num_nodes;
    }
    if((*this).graph.find(head_node) == (*this).graph.end()) {
        (*this).graph[head_node] = new SNode(head_node, 1);
        ++(*this).num_nodes;
    }
    
    Edge new_edge = Edge(tail_node, head_node, weight);
    std::set<Edge>::iterator it = (*this).graph[tail_node]->out_edges.find(new_edge);
    if(it == (*this).graph[tail_node]->out_edges.end()) {
        (*this).graph[tail_node]->out_edges.insert(Edge(tail_node, head_node, weight));
    } else if(weight < it->weight) {
        (*this).graph[tail_node]->out_edges.erase(it);
        (*this).graph[tail_node]->out_edges.insert(Edge(tail_node, head_node, weight));
    }
}

int Digraph::edge_count() const {
    int count = 0;
    for(GraphBase<SNode>::node_iterator it = (*this).begin(); it != (*this).end(); ++it) {
        count += it->out_edges.size();
    }
    return count;
}

std::vector<Edge> Digraph::get_edge_list() const {
    // std::set<Edge> edges;
    std::vector<Edge> edge_list;
    for(GraphBase<SNode>::node_iterator it1 = (*this).begin(); it1 != (*this).end(); ++it1) {
        for(std::set<Edge>::iterator it2 = it1->out_edges.begin(); it2 != it1->out_edges.end(); ++it2) {
            // edges.insert(*it2);
            edge_list.push_back(*it2);
        }
    }
    // std::vector<Edge> edge_list(edges.begin(), edges.end());
    std::sort(edge_list.begin(), edge_list.end(), Edge::edge_sort_by_wt());
    return edge_list;
}

std::map<int, Digraph::wp_pair> Digraph::bellman_ford(int source, const Digraph &digraph, bool &valid) {
    std::map<int, Digraph::wp_pair> previous, current;
    std::vector<Edge> edges = digraph.get_edge_list();
    long distance;  
    
    // find sum of all edge weights and add 1
    distance = 0;
    for(std::vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
        distance += it->weight;
    }
    distance = distance + 1;
    
    // set i=0 shortest paths in current, previous maps
    for(Digraph::node_iterator it = digraph.begin(); it != digraph.end(); ++it) {
        current[it->get_id()] = Digraph::wp_pair(distance, source);
    }
    current[source].distance = 0;
        
    // run Bellman-Ford algorithm n times to check for negative cycles
    valid = false;
    for(int i = 1; i < digraph.node_count(); ++i) {
        previous = current;
        for(std::vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
            distance = previous[it->tail].distance + it->weight;
            if(distance < current[it->head].distance) {
                current[it->head] = Digraph::wp_pair(distance, it->tail);
            }
        }
        if(current == previous) {
            valid = true;
            break;
        }
    }
    
    return previous;    // previous is returned since alg runs one extra cycle
}

std::map<int, Digraph::wp_pair> Digraph::dijkstra_alg(int source, const Digraph &digraph) {
    std::map<int, Digraph::wp_pair> sds;
    int next_node, num_nodes = digraph.node_count();
    long distance;
    
    // store source node and add source node out edges to edge priority queue
    sds[source] = Digraph::wp_pair(0, source);
    std::priority_queue<Edge, std::vector<Edge>, Edge::edge_sort_by_wt> edges;
    for(std::set<Edge>::iterator it = digraph[source].out_edges.begin(); it != digraph[source].out_edges.end(); ++it) {
        edges.push(Edge(source, it->head, -1 * it->weight));    // negative required to maintain proper order in priority queue
    }

    // calculate shortest paths to remaining nodes
    while(sds.size() < num_nodes || edges.empty()) {
        Edge next_edge = edges.top();
        edges.pop();
        if(sds.find(next_edge.head) == sds.end()) {
            next_node = next_edge.head;
            distance = next_edge.weight;
            sds[next_node] = Digraph::wp_pair(-1 * distance, next_edge.tail);   // re-negate distance value
            for(std::set<Edge>::iterator it = digraph[next_node].out_edges.begin(); it != digraph[next_node].out_edges.end(); ++it) {
                edges.push(Edge(next_node, it->head, -1 * it->weight + distance));
            }
        }
    }
    
    return sds;
}

std::map<int, std::map<int, Digraph::wp_pair> > Digraph::johnson_alg(const Digraph &digraph, bool &valid) {
    std::map<int, std::map<int, Digraph::wp_pair> > apsps;
    std::map<int, Digraph::wp_pair> nsps;
    std::map<int, int> node_weights;
    Digraph *gmod;
    
    // add ghost node with 0 weight paths and run bellman-ford to get node weights
    int node = -1;
    while(true) {
        if(digraph.graph.find(node) == digraph.graph.end() || digraph.node_count() == 0) {
            break;
        }
        ++node;
    }
    gmod = new Digraph(digraph);
    for(Digraph::node_iterator it = digraph.begin(); it != digraph.end(); ++it) {
        gmod->add_edge(node, it->get_id(), 0);
    }
    nsps = Digraph::bellman_ford(node, *gmod, valid);
    if(!valid) {
        delete gmod;
        return apsps;
    }
    for(Digraph::node_iterator it = digraph.begin(); it != digraph.end(); ++it) {
        node = it->get_id();
        node_weights[node] = nsps[node].distance;
    }
    delete gmod;
    
    // create new graph and run dijkstra on all remaining nodes
    gmod = new Digraph;
    std::vector<Edge> edge_list = digraph.get_edge_list();
    for(std::vector<Edge>::iterator it = edge_list.begin(); it != edge_list.end(); ++it) {
        gmod->add_edge(it->tail, it->head, it->weight + node_weights[it->tail] - node_weights[it->head]);
    }
    for(Digraph::node_iterator it1 = digraph.begin(); it1 != digraph.end(); ++it1) {
        nsps = Digraph::dijkstra_alg(it1->get_id(), *gmod);
        for(std::map<int, Digraph::wp_pair>::iterator it2 = nsps.begin(); it2 != nsps.end(); ++it2) {
            (it2->second).distance = (it2->second).distance - node_weights[it1->get_id()] + node_weights[it2->first]; 
        }
        apsps[it1->get_id()] = nsps;
    }
    delete gmod;
    
    return apsps;
}

Digraph::wp_pair Digraph::ss_path(const Digraph &digraph, bool &valid) {
    std::map<int, Digraph::wp_pair> nsps;
    Digraph::wp_pair ssp_pair;
    Digraph gmod;
    
    // add ghost node with 0 weight paths and run bellman-ford to get node weights
    int node = -1;
    while(true) {
        if(digraph.graph.find(node) == digraph.graph.end() || digraph.node_count() == 0) {
            break;
        }
        ++node;
    }
    gmod = Digraph(digraph);
    for(Digraph::node_iterator it = digraph.begin(); it != digraph.end(); ++it) {
        gmod.add_edge(node, it->get_id(), 0);
    }
    nsps = Digraph::bellman_ford(node, gmod, valid);
    if(!valid) {
        return Digraph::wp_pair(0, 0);
    } else {
        ssp_pair = nsps.begin()->second;
        for(std::map<int, Digraph::wp_pair>::iterator it = nsps.begin(); it != nsps.end(); ++it) {
            if((it->second).distance < ssp_pair.distance) ssp_pair = it->second;
        }
    }
    
    return ssp_pair;
}
