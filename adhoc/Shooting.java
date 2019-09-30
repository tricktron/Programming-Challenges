/*
Codeforces Round 587 - Shooting - https://codeforces.com/contest/1216/problem/B

Adhoc - Minimize the term a_i * x + 1

Solution: As x is monotonically increasing we sort a_i decreasingly, calculate
        the sum and print the sorted array.
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.StringTokenizer;
import java.util.stream.IntStream;

public final class Shooting {
    static class FastReader 
    { 
        BufferedReader br; 
        StringTokenizer st; 
  
        public FastReader() 
        { 
            br = new BufferedReader(new
                     InputStreamReader(System.in)); 
        }
  
        String next() 
        { 
            while (st == null || !st.hasMoreElements()) 
            { 
                try
                { 
                    st = new StringTokenizer(br.readLine()); 
                } 
                catch (IOException e) 
                { 
                    e.printStackTrace(); 
                } 
            } 
            return st.nextToken(); 
        } 
  
        int nextInt() 
        { 
            return Integer.parseInt(next()); 
        } 
  
        long nextLong() 
        { 
            return Long.parseLong(next()); 
        } 
  
        double nextDouble() 
        { 
            return Double.parseDouble(next()); 
        } 
  
        String nextLine() 
        { 
            String str = ""; 
            try
            { 
                str = br.readLine(); 
            } 
            catch (IOException e) 
            { 
                e.printStackTrace(); 
            } 
            return str; 
        } 
    }

    static class Can {
        int index;
        int durability;

        Can(int i, int d) {
            index = i;
            durability = d;
        }

        /**
         * @return the durability
         */
        public int getDurability() {
            return durability;
        }

        /**
         * @return the index
         */
        public int getIndex() {
            return index;
        }
    }
    
    public static void main(String[] args) {
        FastReader fs = new FastReader();
        List<Can> cans = new ArrayList<>();
        int n = fs.nextInt();
        for (int i = 1; i <= n; i++) {
            int d = fs.nextInt();
            cans.add(new Can(i, d));
        }

        cans.sort(Comparator.comparingInt(Can::getDurability).reversed());
        int sum = IntStream.range(0, cans.size()).map(i -> 
            (i * cans.get(i).durability) + 1).sum();
        System.out.println(sum);
        IntStream.range(0, cans.size() - 1).mapToObj(i -> cans.get(i))
            .forEach(c -> System.out.print(c.index + " "));
        System.out.println(cans.get(cans.size() - 1).index);
    }
}