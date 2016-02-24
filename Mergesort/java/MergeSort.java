import java.util.ArrayList;
import java.math.BigInteger;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class MergeSort
{
    // instance variables - replace the example below with your own
    public static BigInteger inversions = new BigInteger("0");

    public MergeSort() {}
    
    public static void resetInversions() {
        MergeSort.inversions = BigInteger.ZERO;
    }

    public static ArrayList<Integer> merge_sort(ArrayList<Integer> array, int left_ind, int right_ind)
    {
        if(right_ind < 0)
            right_ind = array.size() - 1;
        if(left_ind < 0)
            left_ind = 0;

        if(right_ind - left_ind <= 0) {
            return new ArrayList<Integer>(array.subList(left_ind, left_ind + 1));
        } else {
            int index = (left_ind + right_ind) / 2;
            return merge(merge_sort(array, left_ind, index),
                         merge_sort(array, index + 1, right_ind));
        }
    }
    
    private static ArrayList<Integer> merge(ArrayList<Integer> left, ArrayList<Integer> right)
    {
        int nl = left.size(), nr = right.size(), i = 0, j = 0;
        Integer new_inversions = new Integer(0);
        ArrayList<Integer> merged = new ArrayList<Integer>(nl + nr);
        while(i < nl && j < nr) {
            if(left.get(i) <= right.get(j)) {
                merged.add(left.get(i));
                ++i;
            } else {
                merged.add(right.get(j));
                new_inversions = nl - i;
                MergeSort.inversions = MergeSort.inversions.add(new BigInteger(new_inversions.toString()));
                ++j;
            }
        }

        if(i == nl) {
            for(int k = j; k < nr; ++k) {
                merged.add(right.get(k));
            }
        } else if(j == nr) {
            for(int k = i; k < nl; ++k) {
                merged.add(left.get(k));
            }
        }
        
        return merged;
    }
    
    public static void main() throws FileNotFoundException, IOException {
        // testing();
        long start, finish;
        
        // read input file
        start = System.currentTimeMillis();
        ArrayList<Integer> integer_array = readFile("IntegerArray.txt");
        finish = System.currentTimeMillis();
        long elapsed = finish - start;
        long totalTime = elapsed;
        System.out.println("Time to read input file: " + elapsed + " ms");   // 20 ms
        
        // sort list
        start = System.currentTimeMillis();
        merge_sort(integer_array, -1, -1);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        totalTime += elapsed;
        System.out.println("Time to sort list: " + elapsed + " ms");   // 150 ms
        System.out.println("Total processing time: " + totalTime + " ms");   // 170 ms
        System.out.println();
        
        // print answer
        System.out.println("Number of inversions: " + MergeSort.inversions);
        System.out.println();
        MergeSort.resetInversions();
        
    }
    
    private static void testing() {
        ArrayList<Integer> ex = new ArrayList<Integer>();
        for(int i = 0; i < 10; ++i) {
            ex.add(10 - i);
        }
        ArrayList<Integer> sex = merge_sort(ex, -1, -1);
        for(int j = 0; j < 10; ++j) {
            System.out.print(sex.get(j) + " ");
        }
        System.out.println();
        System.out.println("Array Size: " + sex.size());
        System.out.println("Number of inversions: " + MergeSort.inversions.toString());
    }
    
    private static ArrayList<Integer> readFile(String filename) throws FileNotFoundException, IOException {
        ArrayList<Integer> integer_array = new ArrayList<Integer>();
        BufferedReader inputFile = new BufferedReader(new FileReader("IntegerArray.txt"));
        String line = inputFile.readLine();
        while(line !=  null) {
            integer_array.add(Integer.parseInt(line));
            line = inputFile.readLine();
        }
        inputFile.close();
        return integer_array;
    }
}
