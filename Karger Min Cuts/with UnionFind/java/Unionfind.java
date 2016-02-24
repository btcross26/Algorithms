import java.util.ArrayList;
import java.util.HashSet;

public class Unionfind
{
    final public int SITES;
    private int num_clusters;
    private ArrayList<HashSet<Integer>> setptr;

    /**
     * Constructor for objects of class Unionfind
     */
    public Unionfind(int sites)
    {
        this.SITES = sites;
        this.num_clusters = sites;
        this.setptr = new ArrayList<HashSet<Integer>>();
        for(int i = 0; i < sites; ++i)
        {
            setptr.add(new HashSet(1));
            setptr.get(i).add(i+1);
        }
    }

    public boolean is_connected(int n1, int n2)
    {
        return this.setptr.get(n1-1).contains(n2);
    }
    
    public void merge(int n1, int n2)
    {
        if(!this.is_connected(n1, n2))
        {
            --this.num_clusters;
            int n1_size = this.setptr.get(n1-1).size();
            int n2_size = this.setptr.get(n2-1).size();
            if(n1_size > n2_size)
            {
                this.setptr.get(n1-1).addAll(this.setptr.get(n2-1));
                for(Integer n : this.setptr.get(n2-1))
                {
                    this.setptr.set(n-1, this.setptr.get(n1-1));
                }
            }
            else
            {
                this.setptr.get(n2-1).addAll(this.setptr.get(n1-1));
                for(Integer n : this.setptr.get(n1-1))
                {
                    this.setptr.set(n-1, this.setptr.get(n2-1));
                }
            }
        }
    }
    
    public int get_num_clusters()
    {
        return this.num_clusters;
    }
    
    public HashSet<Integer> get_first_cluster()
    {
        return this.setptr.get(0);
    }
}
