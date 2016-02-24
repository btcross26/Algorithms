import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Collections;
import java.io.*;

class twoSum
{  
    public static void main() throws FileNotFoundException, IOException
    {
        // Vector Based Implementation
        long start = System.currentTimeMillis();
        long answer = two_sum_vector("2sum.txt", -10000, 10000);
        long finish = System.currentTimeMillis();
        long elapsed = finish - start;
        System.out.println("Vector Based Implementation:");
        System.out.println("Computation time: " + elapsed + " milliseconds");
        System.out.println("          Answer: " + answer);
        System.out.println();
        
        // HashMap Based Implementation
        start = System.currentTimeMillis();
        answer = two_sum_hashtable("2sum.txt", -10000, 10000);
        finish = System.currentTimeMillis();
        elapsed = finish - start;
        System.out.println("Hash Table Based Implementation:");
        System.out.println("Computation time: " + elapsed + " milliseconds");
        System.out.println("          Answer: " + answer);
        System.out.println();
    }
    
    public static long two_sum_vector(String filename, int lower, int upper) throws FileNotFoundException, IOException
    {
        // read file and transfer to vector
        BufferedReader input_file = new BufferedReader(new FileReader(filename));
        ArrayList<Long> num_list = new ArrayList<Long>();
        String line = input_file.readLine();
        while(line != null)
        {
            num_list.add(Long.parseLong(line));
            line = input_file.readLine();
        }
        input_file.close();
        Collections.sort(num_list);
        
        // find and return answer
        int min_index = 0;
        int max_index = num_list.size() - 1;
        HashSet<Long> existing_sums = new HashSet<Long>();
        while(max_index > min_index)
        {
            while(num_list.get(min_index) + num_list.get(max_index) > upper && max_index > min_index)
            {
                --max_index;
            }
            for(int i = max_index; i > min_index; --i)
            {
                if(num_list.get(min_index) + num_list.get(i) < lower)
                {
                    break;
                }
                else if(num_list.get(min_index) != num_list.get(i))
                {
                    existing_sums.add(num_list.get(min_index) + num_list.get(i));
                }
            }
            ++min_index;
        }
        return existing_sums.size();
        
    }

    public static long two_sum_hashtable(String filename, int lower, int upper) throws FileNotFoundException, IOException
    {
        // read file and transfer to Hash Table
        BufferedReader input_file = new BufferedReader(new FileReader(filename));
        long range = upper - lower;
        HashMap<Long, HashSet<Long>> num_map = new HashMap<Long, HashSet<Long>>();
        String line = input_file.readLine();
        while(line != null)
        {
            long key = (Long.parseLong(line) - lower) / range;
            if(!num_map.containsKey(key))
            {
                num_map.put(key, new HashSet<Long>());
            }
            num_map.get(key).add(Long.parseLong(line));
            line = input_file.readLine();
        }
        input_file.close();
        
        // find and return answer
        HashSet<Long> existing_sums = new HashSet<Long>();
        Iterator<Long> it1 = num_map.keySet().iterator();
        while(it1.hasNext())
        {
            long key = it1.next();
            if(key <= 0 && num_map.containsKey(-key))
            {
                for(long value1 : num_map.get(key))
                {
                    for(long value2 : num_map.get(-key))
                    {
                        if(value1 + value2 <= range && value1 + value2 >= 0)
                        {
                            existing_sums.add(value1 + value2);
                        }
                    }
                }
            }
            if(key <= 0 && num_map.containsKey(-key + 1))
            {
                for(long value1 : num_map.get(key))
                {
                    for(long value2 : num_map.get(-key + 1))
                    {
                        if(value1 + value2 <= range && value1 + value2 >= 0)
                        {
                            existing_sums.add(value1 + value2);
                        }
                    }
                }
            }
            if(key == 1)
            {
                for(long value1 : num_map.get(key))
                {
                    for(long value2 : num_map.get(key))
                    {
                        if(value1 != value2 && value1 + value2 <= range && value1 + value2 >= 0)
                        {
                            existing_sums.add(value1 + value2);
                        }
                    }
                }
            }
        }
        return existing_sums.size();
        
    
    }

}
