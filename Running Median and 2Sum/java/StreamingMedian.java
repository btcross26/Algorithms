import java.util.PriorityQueue;
import java.io.*;
/**
 * Write a description of class StreamingMedian here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class StreamingMedian
{
    public static void main() throws FileNotFoundException, IOException
    {
        long start = System.currentTimeMillis();
        long s = sum_of_streaming_medians("Median.txt");
        long answer = s % 10000;
        long finish = System.currentTimeMillis();
        long elapsed = finish - start;
        System.out.println("Computation time: " + elapsed + " milliseconds");
        System.out.println("          Answer: " + answer);
        System.out.println();
    }
    
    public static long sum_of_streaming_medians(String filename) throws FileNotFoundException, IOException
    {
        BufferedReader input_file = new BufferedReader(new FileReader(filename));
        PriorityQueue<Integer> min_heap = new PriorityQueue<Integer>();
        PriorityQueue<Integer> max_heap = new PriorityQueue<Integer>();
        String line = input_file.readLine();
        long sum = 0;
        while(line != null)
        {
            int value = Integer.parseInt(line);
            if(min_heap.size() == max_heap.size())
            {
                min_heap.offer(value);
                value = min_heap.poll();
                max_heap.offer(-value);
            }
            else
            {
                max_heap.offer(-value);
                value = -max_heap.poll();
                min_heap.offer(value);
            }
            sum = sum - max_heap.peek();
            line = input_file.readLine();
        }
        input_file.close();
        return sum;
    }
}
