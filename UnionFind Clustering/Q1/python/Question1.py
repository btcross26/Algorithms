class Edge_Priority_Queue(object):   
    def __init__(self):
        import heapq
        self.array = []
        self.index = 0
        heapq.heapify(self.array)
    
    def __len__(self):
        return len(self.array)
        
    def push(self, value):
        import heapq
        assert isinstance(value, Edge)
        value_tuple = (value.weight, self.index, value)
        heapq.heappush(self.array, value_tuple)
        
    def pop(self):
        import heapq
        value = heapq.heappop(self.array)
        return value[2]
        
class Edge(object):
    def __init__(self, tail, head, weight):
        self.tail, self.head, self.weight = tail, head, weight
        
    def __lt__(self, other):
        assert isinstance(other, Edge)
        if self.weight < other.weight:
            return True
        else: return False

class UnionFind(object):
    def __init__(self, sites):
        self.sites = sites
        self.clusters = sites
        self.array = [[ind] for ind in range(sites)]
        
    def connected(self, i, j):
        return id(self.array[i]) == id(self.array[j])
        
    def merge(self, i, j):
        if self.connected(i, j): return        
        self.clusters -= 1
        if len(self.array[i]) > len(self.array[j]):
            large, small = self.array[i], self.array[j]
        else:
            large, small = self.array[j], self.array[i]          
        large += small
        for ind in small:
            self.array[ind] = large
            
    def num_clusters(self):
        return self.clusters
        
    def num_sites(self):
        return self.num_sites
        
def main():
    import time
    
    # reading input file
    start = time.time()
    edgeQueue = Edge_Priority_Queue()
    with open("clustering1.txt", "r") as f:
        for line in f:
            values = [int(value) for value in line.split()]
            if len(values) == 1:
                nodes = int(values[0])
                continue
            tail, head, weight = values
            edgeQueue.push(Edge(tail, head, weight))        
    finish = time.time()
    total_time = (finish - start) * 1e3
    print("Time to read file: %0.1f ms" % total_time)
    print("Remaining edges: ", str(len(edgeQueue)))
    
    # calculate clusters
    start = time.time()
    components = UnionFind(nodes)
    while(components.num_clusters() > 4):
        edge = edgeQueue.pop()
        components.merge(edge.tail - 1, edge.head - 1)
    finish = time.time()
    total_time = (finish - start) * 1e3
    print("Time to run clustering: %0.1f ms" % total_time)

    # find answer
    max_distance = 0
    while True:
        edge = edgeQueue.pop()
        if(not components.connected(edge.tail - 1, edge.head - 1)):
            max_distance = edge.weight
            break
    print("Maximum cluster spacing: ", str(max_distance))
    
    
if __name__ == "__main__":
    main()