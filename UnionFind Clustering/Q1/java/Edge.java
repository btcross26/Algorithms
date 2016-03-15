public class Edge implements Comparable<Edge> {
    private int tail, head, weight;

    public Edge(int tail, int head, int weight) {
        this.tail = tail;
        this.head = head;
        this.weight = weight;
    }

    public int compareTo(Edge other) {
        if(this.weight < other.weight) {
            return -1;
        } else if(this.weight == other.weight) {
            return 0;
        } else return 1;
    }
    
    public int get_tail() { return this.tail; }
    
    public int get_head() { return this.head; }
    
    public int get_weight() { return this.weight; }
}
