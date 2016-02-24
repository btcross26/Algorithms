import java.util.ArrayList;
import java.util.HashSet;
import java.util.Collections;
import java.io.*;

public class KargerEdgeList
{
    // instance variables - replace the example below with your own
    private ArrayList<Uedge> edge_list;
    private int num_nodes;

    public KargerEdgeList(ArrayList<Uedge> edge_list)
    {
        this.edge_list = new ArrayList<Uedge>(edge_list);
        HashSet<Integer> nodes = new HashSet<Integer>();
        for(Uedge edge : edge_list) {
            nodes.add(edge.tail);
            nodes.add(edge.head);
        }
        this.num_nodes = nodes.size();        
    }

    public int minCuts(int iterations)
    {
        int min_cuts = this.edge_list.size();
        for(int i = 0; i < iterations; ++i)
        {
            Collections.shuffle(this.edge_list);
            Unionfind clusters = new Unionfind(this.num_nodes);
            for(Uedge edge : this.edge_list)
            {
                clusters.merge(edge.tail, edge.head);
                if(clusters.get_num_clusters() == 2)
                {
                    break;
                }
            }
            HashSet<Integer> fc = clusters.get_first_cluster();
            int cuts = 0;
            for(Uedge edge : this.edge_list)
            {
                int bit1 = fc.contains(edge.tail) ? 1 : 0;
                int bit2 = fc.contains(edge.head) ? 1 : 0;
                cuts += (bit1 + bit2 == 1) ? 1 : 0;
            }
            if(cuts < min_cuts)
            {
                min_cuts = cuts;
            }
        }
        return min_cuts;
    }
    
    public static ArrayList<Uedge> readFile(String filename) throws FileNotFoundException, IOException
    {
        ArrayList<Uedge> edge_list = new ArrayList<Uedge>();
        BufferedReader inputFile = new BufferedReader(new FileReader(filename));
        String line = inputFile.readLine();
        while(line != null)
        {
            String[] numbers = line.split("\\t");
            int tail = Integer.parseInt(numbers[0]);
            for(int i = 1; i < numbers.length; ++i)
            {
                int head = Integer.parseInt(numbers[i]);
                if(tail < head)
                {
                    edge_list.add(new Uedge(tail, head));
                }
            }
            line = inputFile.readLine();
        }
        inputFile.close();
        return edge_list;
    }
    
    public static void main() throws FileNotFoundException, IOException
    {
        long start, finish, elapsed;
        
        // read file and create edge list vector: 0 ms
        start = System.currentTimeMillis();
        ArrayList<Uedge> edge_list = readFile("KargerMinCut.txt");
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Number of edges read: " + edge_list.size());
        System.out.println("Time to read file: " + elapsed + " ms\n");
        
        // run Karger Min Cuts Algorithm: 2423 ms for 10000 iterations
        int numiters = 10000;
        start = System.currentTimeMillis();
        KargerEdgeList kEdges = new KargerEdgeList(edge_list);
        int minCuts = kEdges.minCuts(numiters);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Number of iterations used: " + numiters);
        System.out.println("Time to perform calculations: " + elapsed + " ms");
        System.out.println("Minimum cuts: " + minCuts + "\n");
        
    }
}
