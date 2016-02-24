public class DynamicArray
{
    // instance variables - replace the example below with your own
    private int[] array;
    private double multiplier;
    private int size;

    public DynamicArray(double mutiplier)
    {
        if(multiplier < 1.0)
        {
            this.multiplier = 1.0;
        }
        else
        {
        this.multiplier = multiplier;
        }
        this.array = new int[1];
        this.size = 0;
    }
    
    public void add(int value)
    {
        if(this.size == this.array.length)
        {
            this.add_capacity();
        }
        this.array[this.size] = value;
        ++this.size;
    }
    
    public int get(int index) throws IndexOutOfBoundsException
    {
        if(index >= this.size)
        {
            throw new IndexOutOfBoundsException();
        }
        return this.array[index];
    }
    
    public void set(int index, int value) throws IndexOutOfBoundsException
    {
        if(index >= this.size)
        {
            throw new IndexOutOfBoundsException();
        }
        this.array[index] = value;
    }
    
    public int size()
    {
        return this.size;
    }
    
    private void add_capacity()
    {
        int[] old_array = this.array;
        int new_size = (int)(this.multiplier * this.array.length);
        if(new_size <= this.array.length)
        {
            this.array = new int[this.array.length + 1];
        }
        else
        {
            this.array = new int[new_size];
        }
        for(int i = 0; i < this.size; ++i) {
            this.array[i] = old_array[i];
        }
    }
}
