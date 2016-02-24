import java.util.ArrayList;
import java.util.HashMap;
import java.util.Stack;
import java.util.Collections;
import java.util.Iterator;
import java.util.Map;
import java.io.*;

public class Digraph
{
    private HashMap<Integer, DynamicArray> alist;

    public Digraph()
    {
        this.alist = new HashMap<Integer, DynamicArray>();
    }
    
    public Digraph(int nodes)
    {
        this.alist = new HashMap<Integer, DynamicArray>(nodes);
    }

    public void add_edge(int tail, int head)
    {
        if(!this.alist.containsKey(tail))
        {
            this.alist.put(tail, new DynamicArray(1.25));
        }
        if(!this.alist.containsKey(head))
        {
            this.alist.put(head, new DynamicArray(1.25));
        }
        this.alist.get(tail).add(head);
    }
    
    public int num_nodes()
    {
        return this.alist.size();
    }
    
    public Digraph transpose()
    {
        Digraph digraph = new Digraph();
        for(Map.Entry<Integer, DynamicArray> entry : this.alist.entrySet())
        {
            int head_node = entry.getKey();
            DynamicArray tnodes = entry.getValue();
            for(int i = 0; i < tnodes.size(); ++i)
            {
                int tail_node = tnodes.get(i);
                digraph.add_edge(tail_node, head_node);
            }
        }
        return digraph;
    }
    
    public ArrayList<Integer> scc_sizes()
    {
        Stack<Integer> to_explore = new Stack<Integer>();
        HashMap<Integer, Integer> dfs_finish = new HashMap<Integer, Integer>(this.alist.size());
        ArrayList<Integer> finished_order = new ArrayList<Integer>(this.alist.size() + 1);
        int finish = 1;
        
        // perform dfs on all vertices of transposed graph
        Digraph t_digraph = this.transpose();
        Iterator it = t_digraph.alist.keySet().iterator();
        while(it.hasNext())
        {
            int key = (int)it.next();
            if(!dfs_finish.containsKey(key))
            {
                to_explore.push(key);
                dfs_finish.put(key, 0);
                while(!to_explore.empty())
                {
                    int stack_size = to_explore.size();
                    for(int i = 0; i < t_digraph.alist.get(to_explore.peek()).size(); ++i)
                    {
                        int node = t_digraph.alist.get(to_explore.peek()).get(i);
                        if(!dfs_finish.containsKey(node))
                        {
                            to_explore.push(node);
                            dfs_finish.put(node, 0);
                        }
                    }
                    if(to_explore.size() == stack_size)
                    {
                        int finished_node = to_explore.pop();
                        dfs_finish.put(finished_node, finish);
                        ++finish;
                    }
                }
            }
        }
        t_digraph = null;
        to_explore = null;
        
        // get and store loop order
        HashMap<Integer, Integer> loop_order = new HashMap<Integer, Integer>(this.alist.size());
        it = dfs_finish.keySet().iterator();
        while(it.hasNext())
        {
            int key = (int)it.next();
            loop_order.put(dfs_finish.get(key), key);
        }
        
        // perform dfs on graph with reverse loop order
        dfs_finish.clear();
        to_explore = new Stack<Integer>();
        ArrayList<Integer> scc_sizes = new ArrayList<Integer>();
        for(int i = this.alist.size(); i > 0; --i)
        {
            if(!dfs_finish.containsKey(loop_order.get(i)))
            {
                int component_size = 0;
                to_explore.push(loop_order.get(i));
                dfs_finish.put(loop_order.get(i), 0);
                while(!to_explore.empty())
                {
                    int stack_size = to_explore.size();
                    for(int j = 0; j < this.alist.get(to_explore.peek()).size(); ++j)
                    {
                        int node = this.alist.get(to_explore.peek()).get(j);
                        if(!dfs_finish.containsKey(node))
                        {
                            to_explore.push(node);
                            dfs_finish.put(node, 0);
                        }
                    }
                    if(to_explore.size() == stack_size)
                    {
                        to_explore.pop();
                        ++component_size;
                    }
                }
                scc_sizes.add(component_size);
            }
        }
        Collections.sort(scc_sizes);
        return scc_sizes;
    }
    
    public static void main() throws FileNotFoundException, IOException
    {
        long start, finish;
        double elapsed;
        
        // read file
        start = System.currentTimeMillis();
        Digraph digraph = read_file("SCC.txt");
        finish = System.currentTimeMillis();
        elapsed = (finish - start) / 1000.0;
        System.out.println("Time to read file: " + elapsed + " seconds");
        System.out.println("Number of graph vertices: " + digraph.num_nodes());
        System.out.println();
        
        // calculate SCC sizes
        start = System.currentTimeMillis();
        ArrayList<Integer> scc_sizes = digraph.scc_sizes();
        finish = System.currentTimeMillis();
        elapsed = (finish - start) / 1000.0;
        System.out.println("Calculation time: " + elapsed + " seconds");
        System.out.println();
        
        // print answer
        int count = 0;
        System.out.print("Component sizes: ");
        for(int i = scc_sizes.size() - 1; i > -1; --i)
        {
            System.out.print(scc_sizes.get(i) + " ");
            ++count;
            if(count == 5)
            {
                break;
            }
        }
        System.out.println();
        System.out.println();
    }
    
    public static Digraph read_file(String filename) throws FileNotFoundException, IOException
    {
        Digraph digraph = new Digraph();
        BufferedReader inputFile = new BufferedReader(new FileReader(filename));
        String line = inputFile.readLine();
        while(line != null)
        {
            String[] numbers = line.split(" ");
            int tail = Integer.parseInt(numbers[0]);
            int head = Integer.parseInt(numbers[1]);
            digraph.add_edge(tail, head);
            line = inputFile.readLine();
        }
        inputFile.close();
        return digraph;
    }
}
