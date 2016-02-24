import java.util.ArrayList;
import java.util.Collections;
import java.io.*;

public class KargerEdgeList
{
    // instance variables - replace the example below with your own
    private ArrayList<Uedge> edge_list;;

    public KargerEdgeList(ArrayList<Uedge> edge_list)
    {
        this.edge_list = new ArrayList<Uedge>(edge_list);
    }

    public int minCuts(int iterations)
    {
        int min_cuts = this.edge_list.size();
        for(int i = 0; i < iterations; ++i) {
            ArrayList<Uedge> edges_copy = new ArrayList<Uedge>();
            for(int j = 0; j < this.edge_list.size(); ++j)
            {
                edges_copy.add(edge_list.get(j).clone());
            }
            Collections.shuffle(edges_copy);
            int cuts = edges_copy.size();
            while(edges_copy.size() > 0)
            {
                cuts = edges_copy.size();
                int tail = edges_copy.get(0).tail;
                int head = edges_copy.get(0).head;
                for(int j = 0; j < edges_copy.size(); ++j)
                {
                    if(edges_copy.get(j).head == head)
                    {
                        edges_copy.get(j).head = tail;
                    }
                    if(edges_copy.get(j).tail == head)
                    {
                        edges_copy.get(j).tail = tail;
                    }
                }
                ArrayList<Uedge> temp = new ArrayList<Uedge>();
                for(int j = 0; j < edges_copy.size(); ++j)
                {
                    if(!Uedge.selfLoop(edges_copy.get(j)))
                    {
                        temp.add(edges_copy.get(j));
                    }
                }
                edges_copy = temp;
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
        
        // run Karger Min Cuts Algorithm: 56200 ms for 10000 iterations
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
