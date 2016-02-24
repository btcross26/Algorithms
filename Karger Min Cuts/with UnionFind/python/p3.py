'''WinPython 3.4.4'''

import time
import numpy as np

# class Uedge
class Uedge(object):
    def __init__(self, tail, head):
        self.tail = tail
        self.head = head
        
    def __str__(self):
        return "Uedge(" + str(self.tail) + ", " + str(self.head) + ")"
        
    def __repr__(self):
        return self.__str__()
        
    def clone(self):
        return Uedge(self.tail, self.head)
    
# read file into list: ~ 10 ms on average
start = time.time()
with open("KargerMinCut.txt", "rt") as f:
    edge_list = []
    for line in f:
        line = line.strip()
        values = line.split("\t")
        tail = int(values[0])
        edge_list.extend([Uedge(tail, int(head)) for head in values[1:] if tail < int(head)])
finish = time.time()
elapsed = 1000.0 * (finish - start)
print("Time to read file: %.0f ms" % (elapsed,))


# UnionFind class
class UnionFind(object):
    def __init__(self, num_nodes):
        self.num_clusters = num_nodes
        self.setptr = [set([i]) for i in range(1, num_nodes + 1)]
        
    def is_connected(self, n1, n2):
        return id(self.setptr[n1-1]) == id(self.setptr[n2-1])
        
    def merge(self, n1, n2):
        if not self.is_connected(n1, n2):
            self.num_clusters -= 1
            if len(self.setptr[n1-1]) >= len(self.setptr[n2-1]):
                self.setptr[n1-1].update(self.setptr[n2-1])
                for ind in self.setptr[n2-1]:
                    self.setptr[ind-1] = self.setptr[n1-1]
            else:
                self.setptr[n2-1].update(self.setptr[n1-1])
                for ind in self.setptr[n1-1]:
                    self.setptr[ind-1] = self.setptr[n2-1]
        
# KargerEdgeList class
class KargerEdgeList(object):
    def __init__(self, edge_list):
        self.edge_list = list(edge_list)
        self.rpos = len(edge_list)
        self.num_nodes = len({value for edge in edge_list for value in (edge.tail, edge.head)})
        
    def min_cuts(self, iterations):
        min_cuts = len(self.edge_list)
        for i in range(iterations):
            clusters = UnionFind(self.num_nodes)
            cuts = 0
            self.reset_reg()
            while clusters.num_clusters > 2:
                self.random_edge_swap()
                clusters.merge(self.edge_list[self.rpos].tail, self.edge_list[self.rpos].head)
            for j in range(self.rpos):
                if not clusters.is_connected(self.edge_list[j].tail, self.edge_list[j].head):
                    cuts += 1
            if cuts < min_cuts:
                min_cuts = cuts
        return min_cuts
    
    def random_edge_swap(self):
        self.rpos -= 1
        next = np.random.randint(0, self.rpos)
        self.swap_edge(next, self.rpos)
        
    def reset_reg(self):
        self.rpos = len(self.edge_list)
        
    def swap_edge(self, i1, i2):
        self.edge_list[i1], self.edge_list[i2] = self.edge_list[i2], self.edge_list[i1]

# problem solution: total time = 30.623 seconds (28 times slower than c++)
start = time.time()
numiters = 10000
k_edges = KargerEdgeList(edge_list)
min_cuts = k_edges.min_cuts(numiters)
finish = time.time()
elapsed = 1000.0 * (finish - start)
print("Number of iterations: %d" % (numiters,))
print("Time to run algorithm: %.0f ms" % (elapsed,))
print("Minimum cuts: %d" % (min_cuts,))