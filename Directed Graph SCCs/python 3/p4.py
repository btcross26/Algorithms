'''WinPython 3.4.4 64-bit'''

import time
from Digraph import Digraph

# read file: 14.1 seconds
start = time.time()
digraph = Digraph()    
with open("SCC.txt", "rt") as f:
    for line in f:
        tail, head = [int(value) for value in line.split()]
        digraph.add_edge(tail, head)
finish = time.time()
elapsed = 1.0 * (finish - start)
print("Time to read file: %.3f" % (elapsed,))
print("Number of graph vertices: %d" % (digraph.num_nodes(),))
print()

# calculate scc sizes: 9.100 seconds
# answer: 
start = time.time()
scc_sizes = digraph.scc_sizes()
finish = time.time()
elapsed = 1.0 * (finish - start)
print("Calculation time: %.3f" % (elapsed,))

# print out answer
print("Component sizes: ", end="")
for i in range(5):
    print("%d " % (scc_sizes[i],), end="")
print()
print()
