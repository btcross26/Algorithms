'''WinPython 3.4.4'''

import time
from queue import PriorityQueue as pq


class Edge(object):
    def __init__(self, node1, node2, weight):
        self.node1 = node1
        self.node2 = node2
        self.weight = weight
        
    def __str__(self):
        return "(" + str(self.node1) + ", " + str(self.node2) + ", " + \
            str(self.weight) + ")"
            
    def __repr__(self):
        string = self.__str__()
        return "Edge" + string
        
    def __lt__(self, other):
        return self.weight < other.weight
        
    def clone(self):
        return Edge(self.node1, self.node2, self.weight)

        
class Graph(object):
    '''
    Undirected graph, edges are handled accordingly
    '''
    
    def __init__(self):
        self.alist = dict()
        self.edge_list = []
        
    def print_out_edges(self, node):
        out_edges = self.alist[node]
        if len(out_edges) == 0:
            print("Node %d Out Edges: NA" % (node,))
        else:
            print("Node %d Out Edges: " % (node,), end="")
            for edge in out_edges:
                out_node = edge.node2 if edge.node1 == node else edge.node1
                print("(%d, %d)" % (out_node, edge.weight), end=" ")
            print()
                
    def add_edge(self, node1, node2, weight):
        if node1 not in self.alist:
            self.alist[node1] = []
        if node2 not in self.alist:
            self.alist[node2] = []
        edge = Edge(node1, node2, weight)
        self.edge_list.append(edge)
        self.alist[node1].append(edge)
        self.alist[node2].append(edge)
        
    def num_vertices(self):
        return len(self.alist)
        
    def num_edges(self):
        return len(self.edge_list)
        
    @staticmethod
    def shortest_paths(graph, source_node):
        distances = dict()
        edges = pq()
        distances[source_node] = 0
        for edge in graph.alist[source_node]:
            if edge.node1 == source_node:
                edges.put(edge.clone())
            else:
                edges.put(Edge(edge.node2, edge.node1, edge.weight))
        while len(distances) < len(graph.alist) and edges:
            next_edge = edges.get()
            if next_edge.node2 not in distances:
                next_node = next_edge.node2
                distances[next_node] = next_edge.weight
                for edge in graph.alist[next_node]:
                    next_next_node = edge.node2 if edge.node1 == next_node else edge.node1
                    if next_next_node not in distances:
                        edges.put(Edge(next_node, next_next_node, next_edge.weight + edge.weight))
                    # if edge.node1 == next_node:
                        # edges.put(Edge(next_node, edge.node2, next_edge.weight + edge.weight))
                    # else:
                        # edges.put(Edge(next_node, edge.node1, next_edge.weight + edge.weight))
        return distances
        
# read file and build graph
start = time.time()
graph = Graph()
with open("dijkstraData.txt", "rt") as f:
    for line in f:
        values = line.strip().split("\t")
        node1 = int(values[0])
        for index in range(1, len(values)):
            node2, weight = [int(num) for num in values[index].split(",")]
            if node1 < node2:
                graph.add_edge(node1, node2, weight)
finish = time.time()
elapsed = 1000.0 * (finish - start)
print("Time to read file: {0:.3f} ms".format(elapsed))
print()

# calculate shortest paths
start = time.time()
distances = Graph.shortest_paths(graph, 1)
finish = time.time()
elapsed = 1000.0 * (finish - start)
print("Time to calculate shortest paths: {0:.3f} ms".format(elapsed))
print()

# print out answer:
nodes = (7, 37, 59, 82, 99, 115, 133, 165, 188, 197)
print("Answer: ", end="")
for node in nodes:
    if node not in distances:
        print("1000000", end="")
    else:
        print(str(distances[node]), end="")
    if node != 197:
        print(",", end="")
print()