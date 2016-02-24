public class Uedge
{
    // instance variables
    public int tail;
    public int head;

    public Uedge(int tail, int head)
    {
        this.tail = tail;
        this.head = head;
    }
    
    public Uedge clone()
    {
        return new Uedge(this.tail, this.head);
    }

    public static boolean selfLoop(Uedge edge)
    {
        return edge.tail == edge.head;
    }
}
