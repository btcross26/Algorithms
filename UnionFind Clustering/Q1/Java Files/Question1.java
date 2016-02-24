import java.util.PriorityQueue;
import java.io.*;

public class Question1
{

    public static void main(String[] args) throws FileNotFoundException, IOException {
        long startTime, finishTime, totalTime;
        EdgeQueue edgeQueue = new EdgeQueue("clustering1.txt");
        
        // compute clusters
        System.out.println("Computing clusters...");
        startTime = System.currentTimeMillis();
        UnionFind clusters = new UnionFind(edgeQueue.num_nodes());
        compute_clusters(clusters, edgeQueue, 4);        
        finishTime = System.currentTimeMillis();
        totalTime = finishTime - startTime;
        System.out.println("Computation time: " + totalTime + " ms");
        System.out.println("Remaining edges in list: " + edgeQueue.size());
        
        // output final answer
        int max_distance = 0;
        while(true) {
            Edge edge= edgeQueue.pop();
            if(!clusters.connected(edge.get_tail() - 1, edge.get_head() - 1)) {
                max_distance = edge.get_weight();
                break;
            }
        }
        System.out.println("Maximum distance: " + max_distance + "\n");        
    }
    
    public static void compute_clusters(UnionFind components, EdgeQueue edgeQueue, int clusters) {
        Edge edge;
        while(components.num_clusters() > clusters) {;
            edge = edgeQueue.pop();
            components.merge(edge.get_tail() - 1, edge.get_head() - 1);
        }
    }
}
