import java.util.HashMap;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.io.*;

// undirected graph, edges are handled accordingly
public class Graph
{
    private HashMap<Integer, ArrayList<Edge> > alist;
    private ArrayList<Edge> edge_list;
    
    private class Edge implements Comparable<Edge>
    {
        // instance variables - replace the example below with your own
        public int node1;
        public int node2;
        public int weight;
    
        public Edge(int node1, int node2, int weight)
        {
            this.node1 = node1;
            this.node2 = node2;
            this.weight = weight;
        }
        
        public int compareTo(Edge other)
        {
            return this.weight - other.weight;
        }
    }

    public Graph()
    {
        this.alist = new HashMap<Integer, ArrayList<Edge> >();
        this.edge_list = new ArrayList<Edge>();
    }
    
    public void printOutEdges(int node)
    {
        if(!this.alist.containsKey(node))
        {
            System.out.println("KeyError: No node " + node + " in graph!");
        }
        else
        {
            ArrayList<Edge> out_edges = this.alist.get(node);
            if(out_edges == null || out_edges.size() == 0)
            {
                System.out.println("Node " + node + " Out Edges: NA");
            }
            else
            {
                System.out.print("Node " + node + " Out Edges: ");
                for(Edge edge : out_edges)
                {
                    int out_node = (edge.node1 == node) ? edge.node2 : edge.node1;
                    System.out.print("(" + out_node + ", " + edge.weight + ") ");
                }
                System.out.println();
            }
        }
    }
    
    public void addEdge(int node1, int node2, int weight)
    {
        Edge new_edge = new Edge(node1, node2, weight);
        this.edge_list.add(new_edge);
        if(this.alist.get(node1) == null)
        {
            this.alist.put(node1, new ArrayList<Edge>());
        }
        if(this.alist.get(node2) == null)
        {
            this.alist.put(node2, new ArrayList<Edge>());
        }
        this.alist.get(node1).add(new_edge);
        this.alist.get(node2).add(new_edge);
    }
    
    public int vertexCount()
    {
        return this.alist.size();
    }
    
    public int edgeCount()
    {
        return this.edge_list.size();
    }
    
    public HashMap<Integer, Integer> shortestPaths(int sourceNode)
    {
        HashMap<Integer, Integer> distances = new HashMap<Integer, Integer>(this.alist.size());
        PriorityQueue<Edge> edges = new PriorityQueue<Edge>();
        
        distances.put(sourceNode, 0);
        for(Edge edge : this.alist.get(sourceNode))
        {
            int out_node = (edge.node1 == sourceNode) ? edge.node2 : edge.node1;
            edges.offer(new Edge(sourceNode, out_node, edge.weight));
        }
        
        while(!edges.isEmpty() && distances.size() < this.alist.size())
        {
            Edge next_edge = edges.poll();
            if(!distances.containsKey(next_edge.node2))
            {
                int next_node = next_edge.node2;
                distances.put(next_node, next_edge.weight);
                for(Edge edge : this.alist.get(next_node))
                {
                    int next_next_node = (edge.node1 == next_node) ? edge.node2 : edge.node1;
                    if(!distances.containsKey(next_next_node))
                    {
                        edges.offer(new Edge(next_node, next_next_node, next_edge.weight + edge.weight));
                    }
                }
            }
        }
        return distances;        
    }
    
    public static void main() throws FileNotFoundException, IOException
    {
        long start, finish, elapsed;
        
        start = System.currentTimeMillis();
        Graph graph = readFile("dijkstraData.txt");
        HashMap<Integer, Integer> distances = graph.shortestPaths(1);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Time to run program: " + elapsed + " milliseconds");
        System.out.println(" Graph vertex count: " + graph.vertexCount());
        System.out.println("   Graph edge count: " + graph.edgeCount());
        
        int[] nodes = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
        System.out.print("Answer: ");
        for(int i = 0; i < nodes.length; ++i)
        {
            if(!distances.containsKey(nodes[i]))
            {
                System.out.print("1000000");
            }
            else
            {
                System.out.print(distances.get(nodes[i]));
            }
            if(i < nodes.length - 1)
            {
                System.out.print(",");
            }
        }
        System.out.print("\n\n");
    }
    
    public static Graph readFile(String filename) throws FileNotFoundException, IOException
    {
        BufferedReader inputFile = new BufferedReader(new FileReader(filename));
        Graph graph = new Graph();
        String line = inputFile.readLine();
        while(line != null)
        {
            String[] entries = line.split("\t");
            int node1 = Integer.parseInt(entries[0]);
            for(int i = 1; i < entries.length; ++i)
            {
                String[] numbers = entries[i].split(",");
                int node2 = Integer.parseInt(numbers[0]);
                int weight = Integer.parseInt(numbers[1]);
                if(node1 < node2)
                {
                    graph.addEdge(node1, node2, weight);
                }
            }
            line = inputFile.readLine();
        }
        inputFile.close();
        return graph;
    }
}
