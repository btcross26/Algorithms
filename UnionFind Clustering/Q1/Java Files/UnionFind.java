import java.util.ArrayList;

/**
 * UnionFind Class
 * 
 * @author Ben Cross 
 * @version 05182015
 */
public class UnionFind
{
    private int sites;
    private int cluster_count;
    private ArrayList< ArrayList<Integer> > cluster_array;
    
    public UnionFind(int N) {
        this.sites = N;
        this.cluster_count = N;
        this.cluster_array = new ArrayList< ArrayList<Integer> >();
        for(int i = 0; i < N; ++i) {
            this.cluster_array.add(new ArrayList<Integer>());
            this.cluster_array.get(i).add(i);
        }
    }
    
    public boolean connected(int i, int j) {
        return this.cluster_array.get(i) == this.cluster_array.get(j);
    }
    
    public void merge(int i, int j) {
        if(this.connected(i, j)) return;
        
        --this.cluster_count;
        ArrayList<Integer> large, small;
        if(this.cluster_array.get(i).size() > this.cluster_array.get(j).size()) {
            large = this.cluster_array.get(i);
            small = this.cluster_array.get(j);
        } else {
            large = this.cluster_array.get(j);
            small = this.cluster_array.get(i);
        }
        // large.addAll(small);
        for(int index : small) {
            large.add(index);
            this.cluster_array.set(index, large);
        }
    }
    
    public int num_sites() { return this.sites; }
    
    public int num_clusters() { return this.cluster_count; }
       
    public static void main(String[] args) {
    }
}
