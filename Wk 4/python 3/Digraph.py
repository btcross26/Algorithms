class Digraph(object):
    '''Digraph class with functions to compute SCC sizes'''
    def __init__(self):
        self.alist = dict()
    
    def __str__(self):
        return "Digraph()"
        
    def __repr__(self):
        return "Digraph()"
    
    def num_nodes(self):
        return len(self.alist)
        
    def add_edge(self, tail, head):
        if tail not in self.alist:
            self.alist[tail] = list()
        if head not in self.alist:
            self.alist[head] = list()
        self.alist[tail].append(head)
        
    def transpose(self):
        digraph = Digraph()
        for key in self.alist:
            head_node = key
            for tail_node in self.alist[key]:
                digraph.add_edge(tail_node, head_node)
        return digraph
        
    def scc_sizes(self):
        to_explore = list()
        loop_order = [0] * len(self.alist)
        dfs_finish = set()
        finish = 0
        
        # perform dfs on transposed graph
        t_digraph = self.transpose()
        for key in t_digraph.alist:
            if key not in dfs_finish:
                to_explore.append(key)
                dfs_finish.update([key])
                while to_explore:
                    stack_size = len(to_explore)
                    for node in t_digraph.alist[to_explore[-1]]:
                        if node not in dfs_finish:
                            to_explore.append(node)
                            dfs_finish.update([node])
                    if len(to_explore) == stack_size:
                        finished_node = to_explore.pop()
                        loop_order[finish] = finished_node
                        finish += 1
                                   
        # perform dfs on graph with reverse loop order
        dfs_finish = set()
        scc_sizes = []
        for i in range(len(self.alist) - 1, -1, -1):
            if loop_order[i] not in dfs_finish:
                component_size = 0
                to_explore.append(loop_order[i])
                dfs_finish.update([loop_order[i]])
                while to_explore:
                    stack_size = len(to_explore)
                    for node in self.alist[to_explore[-1]]:
                        if node not in dfs_finish:
                            to_explore.append(node)
                            dfs_finish.update([node])
                    if len(to_explore) == stack_size:
                        to_explore.pop()
                        component_size += 1
                scc_sizes.append(component_size)
        scc_sizes.sort(reverse=True)
        return scc_sizes