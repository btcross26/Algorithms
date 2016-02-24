'''WinPython 3.4.4'''

from time import time
import heapq

def sum_of_streaming_medians(filename):           
    s, min_heap, max_heap = 0, [], []
    with open(filename, "rt") as f:
        for value in f:
            value = int(value)
            if len(max_heap) == len(min_heap):
                value = heapq.heappushpop(min_heap, value)
                heapq.heappush(max_heap, -value)
            else:
                value = heapq.heappushpop(max_heap, -value)
                heapq.heappush(min_heap, -value)
            s += -max_heap[0]
        return s

# time = 0.015 seconds    
start = time()
s = sum_of_streaming_medians("Median.txt")
finish = time()
elapsed = 1.0 * (finish - start)
print("Computation time: %.3f seconds" % (elapsed,))
print("          Answer: %d" % (s % 10000,))
print()