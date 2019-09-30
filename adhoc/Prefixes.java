/*
Codeforces Round 587 - Prefixes - https://codeforces.com/contest/1216/problem/A

Adhoc - Create even prefixes. An even prefix is ['ab']. Just loop through the
        array with two step increases and:
        if the first character matches the second:
            1. increase count
            2. change first character
        
        Print count and changed string
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public final class Prefixes {
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

    static class Pair {
        char fst;
        char snd;

        Pair(char fst, char snd) {
            this.fst = fst;
            this.snd = snd;
        }

        @Override
        public String toString() {
            // TODO Auto-generated method stub
            return new StringBuilder(fst).append(snd).toString();
        }
    }
    
    public static void main(String[] args) {
        FastReader fs = new FastReader();
        int n = fs.nextInt();
        int modifications = 0;
        char s[] = fs.nextLine().toCharArray();
        for (int j = 1; j < s.length; j += 2) {
            char fst = s[j - 1];
            char snd = s[j];
            if (fst == snd) {
                s[j - 1] = (fst == 'a') ? 'b' : 'a';
                modifications++;
            }
        }
        System.out.println(modifications);
        System.out.println(s);
        }
}