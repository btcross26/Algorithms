#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iterator>

template<typename T>
class Graph {
    public:
    	Graph() {}
        Graph(std::map<T, std::vector<T> > graph, std::map<T, std::vector<T> > weights);
		Graph<T> calculate_min_spanning_tree();
		T get_total_weight();
				      
    private:
        std::map<T, std::vector<T> > adjacency_list;
        std::map<T, std::vector<T> > weights;
        std::map<T, std::vector< std::vector<T> > > weighted_edge_list; // weights are negated for inclusion in priority_queue
};

/* implementation of generic template class Graph methods */

// public:
template<typename T>
Graph<T>::Graph(std::map<T, std::vector<T> > graph, std::map<T, std::vector<T> > weights)
: adjacency_list(graph), weights(weights) {
	typedef typename std::map<T, std::vector<T> >::iterator iter_map;
	std::vector<T> edge;
	T weight, far;
	
	for(iter_map it1 = adjacency_list.begin(); it1 != adjacency_list.end(); ++it1) {
		for(int i = 0; i < (*it1).second.size(); i++) {
			edge.push_back(-1 * weights[(*it1).first][i]);
			edge.push_back((*it1).first);
			edge.push_back(adjacency_list[(*it1).first][i]);
			weighted_edge_list[(*it1).first].push_back(edge);
			edge.clear();
		}
	}
}
        	
template<typename T>
Graph<T> Graph<T>::calculate_min_spanning_tree() {
	typedef typename std::map<T, std::vector< std::pair<T, T> > >::iterator iter_map;
	typedef typename std::vector< std::vector<T> >::iterator iter_vec;
	std::map<T, std::vector<T> > tree_adjacency_list, tree_weights;
    std::set<T> explored;
    std::priority_queue< std::vector<T> > edge_list;
	T node, far_node, cost;
	
	// initial edge
	node = (*(adjacency_list.begin())).first;
	explored.insert(node);
		
	// loop through edge list	
	while(explored.size() < adjacency_list.size()) {
        for(iter_vec it1 = weighted_edge_list[node].begin(); it1 != weighted_edge_list[node].end(); ++it1) {
            if(explored.find((*it1)[2]) == explored.end()) {
                edge_list.push((*it1));
            }
        }
        while(!edge_list.empty()) {
			if(explored.find(edge_list.top()[2]) == explored.end()) {
                cost = -1 * edge_list.top()[0];
                far_node = edge_list.top()[2];
                edge_list.pop();
				break;
			}
            edge_list.pop();
        }
		tree_adjacency_list[node].push_back(far_node);
		tree_adjacency_list[far_node].push_back(node);
		tree_weights[node].push_back(cost);
		tree_weights[far_node].push_back(cost);
		node = far_node;
		explored.insert(node);
	}

	return Graph<T>(tree_adjacency_list, tree_weights);
}

template<typename T>
T Graph<T>::get_total_weight() {
	typedef typename std::map<T, std::vector<T> >::iterator iter_map;
	typedef typename std::vector<T>::iterator iter_vec;
	T total_weight = 0;
	
	for(iter_map it1 = weights.begin(); it1 != weights.end(); it1++) {
		for(iter_vec it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++) {
			total_weight += (*it2);
		}
	}
	
	return total_weight / 2;
}

#endif
