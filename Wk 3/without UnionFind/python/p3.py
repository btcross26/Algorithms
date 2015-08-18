'''WinPython 3.4.4'''

import time
import random

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
        
    @staticmethod
    def self_loop(edge):
        return edge.tail == edge.head
    
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


# KargerEdgeList class
class KargerEdgeList(object):
    def __init__(self, edge_list):
        self.edge_list = list(edge_list)
        
    def min_cuts(self, iterations):
        min_cuts = len(self.edge_list)
        for i in range(iterations):
            edges_copy = [edge.clone() for edge in self.edge_list]
            random.shuffle(edges_copy)
            while edges_copy:
                cuts = len(edges_copy)
                tail, head = edges_copy[0].tail, edges_copy[0].head
                for index in range(len(edges_copy)):
                    if edges_copy[index].head == head:
                        edges_copy[index].head = tail
                    if edges_copy[index].tail == head:
                        edges_copy[index].tail = tail
                edges_copy = list(filter(lambda edge: not Uedge.self_loop(edge), edges_copy))
            if cuts < min_cuts:
                min_cuts = cuts
        return min_cuts

# problem solution: total time = 249902 ms (28 times slower than c++)
start = time.time()
numiters = 1000
k_edges = KargerEdgeList(edge_list)
min_cuts = k_edges.min_cuts(numiters)
finish = time.time()
elapsed = 1000.0 * (finish - start)
print("Number of iterations: %d" % (numiters,))
print("Time to run algorithm: %.0f ms" % (elapsed,))
print("Minimum cuts: %d" % (min_cuts,))