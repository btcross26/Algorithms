import java.util.ArrayList;
import java.io.*;

public class QuickSort
{
    // instance variables - replace the example below with your own
    private static long comparisons;

    public QuickSort()
    {
        // initialise instance variables
        this.comparisons = 0;
    }

    public static void quicksort(ArrayList<Integer> array, int left, int right, int method)
    {
        if(right - left < 1) {
            return;
        } else {
            QuickSort.comparisons += right - left;
            int pivot = QuickSort.pivot_index(array, left, right, method);
            int pivot_value = array.get(pivot);
            int temp = array.get(left);
            array.set(left, array.get(pivot));
            array.set(pivot, temp);
            pivot = left;
            for(int i = left + 1; i <= right; ++i) {
                if(array.get(i) < pivot_value) {
                    temp = array.get(i);
                    array.set(i, array.get(pivot + 1));
                    array.set(pivot + 1, temp);
                    ++pivot;
                }
            }
            temp = array.get(left);
            array.set(left, array.get(pivot));
            array.set(pivot, temp);
            quicksort(array, left, pivot - 1, method);
            quicksort(array, pivot + 1, right, method);
        }
    }
    
    private static int pivot_index(ArrayList<Integer> array, int left, int right, int method)
    {
        switch(method) {
            case 2:
                return right;
            case 3:
                int middle_index = (left + right) / 2;
                int[] values = new int[] {left, middle_index, right};
                int temp;
                if(array.get(values[1]) < array.get(values[0])) {
                    temp = values[0];
                    values[0] = values[1];
                    values[1] = temp;
                }
                if(array.get(values[2]) < array.get(values[1])) {
                    temp = values[1];
                    values[1] = values[2];
                    values[2] = temp;
                }
                if(array.get(values[1]) < array.get(values[0])) {
                    temp = values[0];
                    values[0] = values[1];
                    values[1] = temp;
                }
                return values[1];
            case 1:
            default:
                return left;            
        }
    }
    
    public static void reset_comparisons()
    {
        QuickSort.comparisons = 0;
    }
    
    public static long get_comparisons()
    {
        return QuickSort.comparisons;
    }
    
    public static void main() throws FileNotFoundException, IOException
    {
        long start, finish, elapsed;
        
        // read input file
        start = System.currentTimeMillis();
        ArrayList<Integer> array = readFile("QuickSort.txt");
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Time to read file: " + elapsed + " ms\n");
       
        
        // Part I: 0 ms
        ArrayList<Integer> array_copy = new ArrayList<Integer>(array);
        start = System.currentTimeMillis();
        QuickSort.quicksort(array_copy, 0, array_copy.size() - 1, 1);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Time to sort list: " + elapsed + " ms");
        System.out.println("Number of comparisons: " + QuickSort.comparisons + "\n");
        QuickSort.reset_comparisons();
        
        // Part II: 0 ms
        array_copy = new ArrayList<Integer>(array);
        start = System.currentTimeMillis();
        QuickSort.quicksort(array_copy, 0, array_copy.size() - 1, 2);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Time to sort list: " + elapsed + " ms");
        System.out.println("Number of comparisons: " + QuickSort.comparisons + "\n");
        QuickSort.reset_comparisons();
        
        // Part III: 10 ms
        array_copy = new ArrayList<Integer>(array);
        start = System.currentTimeMillis();
        QuickSort.quicksort(array_copy, 0, array_copy.size() - 1, 3);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Time to sort list: " + elapsed + " ms");
        System.out.println("Number of comparisons: " + QuickSort.comparisons + "\n\n");
        QuickSort.reset_comparisons();
    }
    
    public static ArrayList<Integer> readFile(String filename) throws FileNotFoundException, IOException
    {
        ArrayList<Integer> array = new ArrayList<Integer>();
        BufferedReader inputFile = new BufferedReader(new FileReader(filename));
        String line = inputFile.readLine();
        while(line != null) {
            array.add(Integer.parseInt(line));
            line = inputFile.readLine();
        }
        inputFile.close();
        return array;
    }
}
