import java.util.PriorityQueue;
import java.io.*;

public class EdgeQueue {
    // instance variables - replace the example below with your own
    private PriorityQueue<Edge> edgeQueue;
    private int nodes;

    public EdgeQueue(String fileName) throws FileNotFoundException, IOException {       
        BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName));
        boolean firstLine = true;
        String line;
        this.edgeQueue = new PriorityQueue<Edge>();
        while((line = bufferedReader.readLine()) != null) {
            if(firstLine) {
                firstLine = false;
                this.nodes = Integer.parseInt(line);
                continue;
            }
            String[] values = line.split(" ");
            int tail = Integer.parseInt(values[0]);
            int head = Integer.parseInt(values[1]);
            int weight = Integer.parseInt(values[2]);
            Edge edge = new Edge(tail, head, weight);
            this.edgeQueue.add(edge);
        }
        bufferedReader.close();
    }
    
    public Edge pop() {
        Edge nextEdge = this.edgeQueue.poll();
        return nextEdge;
    }
    
    public int size() {
        return this.edgeQueue.size();
    }
    
    public int num_nodes() { return this.nodes; }
}
