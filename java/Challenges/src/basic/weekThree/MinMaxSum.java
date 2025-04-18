package basic;

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

class Result {

    /*
     * Complete the 'miniMaxSum' function below.
     *
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static void miniMaxSum(List<Integer> arr) {
    // Write your code here
    Collections.sort(arr);
    
    
    int maxSum = 0;
    int minSum = 0;
    int size = arr.size();
    
    for (int i = 0; i <size; i++){
        if (i == 0){
            minSum += arr.get(i);

            
        }
        else if (i == arr.size()-1){
            maxSum += arr.get(i);
        }
        else{
            minSum += arr.get(i);
            maxSum += arr.get(i);
        }
    }
    
    System.out.printf("%d %d%n", minSum, maxSum);

    }
    
    public static String timeConversion(String s) {
        // Write your code here
        
    	StringBuffer newS = new StringBuffer();
        Integer hh = Integer.parseInt(s.substring(0,2));
        if (s.substring(s.length()-2).equals("PM")){
        	if(hh != 12) {
            hh += 12;
        	}
            newS.append(hh);
            newS.append(s.substring(2, s.indexOf("PM")));
        }
        else{
            if(hh == 12){
                newS.append("00");
                newS.append(s.substring(2, s.indexOf("AM")));
            }
            else {
            	newS.append(s.substring(0,s.length()-2));
            }
        }
        
        return newS.toString();
        
    }

    public static int divisibleSumPairs(int n, int k, List<Integer> ar) {
        // Write your code here
        
        Collections.sort(ar);
        int total = 0;
        
        for (int i = 0; i < ar.size(); i++){
            for (int j = i+1; j < ar.size(); j++){
            	System.out.println( ar.get(i) + "  " + ar.get(j) + "  " +  ((ar.get(i) + ar.get(j)) % k));
            	
                if (((ar.get(i) + ar.get(j)) % k) == 0){
                    total++;
                    //System.out.println(ar.get(i) + " codition met  " + ar.get(j));
                }
               // System.out.println(ar.get(i) + " " + ar.get(j));
            }
        }
        
        return total;

        }
    
    public static int lonelyinteger(List<Integer> a) {
        // Write your code here
        
Collections.sort(a);
        
        boolean duplicate = false; 
        int unique = a.get(0);
        
        for (int i = 1; i < a.size() ; i++){
            
            //System.out.print(a.get(i-1) + " " + a.get(i));
            if (i == a.size()-1){
                return a.get(i);
            }
            else if(unique != a.get(i) && !duplicate){
                return unique;
            }
            else if (unique != a.get(i)) {
                unique = a.get(i);
                duplicate = false;
            }
            else{
                duplicate = true;
            }
            
           // System.out.print(" " + duplicate + "\n");
           
        }
       return unique;
    }
    
    public static long flippingBits(long n) {
        // Write your code here
    	
    	// Final answer
    	long result = 0;
        // Array to keep track of the bits
        int[] bits = new int[32];
        
        for (int i = 0; i < bits.length; i++){
            bits[i] = 0;
        }
        
        //Change dec to bin
        long qoutient = n;
        int remainder = -1;
        for (int i = 0; qoutient != 0; i++){
            if ((qoutient % 2) == 1){
                bits[i] = 1; 
            }  
            qoutient /= 2;
        }
        
        
        for (int i = 0; i < bits.length; i++){
            System.out.print(bits[i] + " " );
        }
        System.out.println();

        
        
        // Flip the bits 
        for (int i = 0; i < bits.length; i++){
            if (bits[i] == 0) {
            	bits[i] = 1;
            }
            else {
            	bits[i] = 0;
            }
        }
        
  
        for (int i = 0; i < bits.length; i++){
            System.out.print(bits[i] + " " );
        }
        System.out.println();
        
        // Change from bin to dec
        
        for (int i = 0; i < bits.length; i++){
            result = (long) (bits[i] * Math.pow(2, i));
        }
        return result;
        
    }
    
   

}

public class MinMaxSum {
    public static void main(String[] args) throws IOException {

        List<Integer> arr = new ArrayList<>();
        arr.add(2);
        arr.add(5);
        arr.add(1);
        arr.add(3);
        arr.add(4);
        
        List<Integer> ar = new ArrayList<>();
        ar.add(1);
        ar.add(3);
        ar.add(2);
        ar.add(6);
        ar.add(1);
        ar.add(2);
        
        List<Integer> a = new ArrayList<>();
        a.add(34);
        a.add(95);
        a.add(34);
        a.add(64);
        a.add(45);
        a.add(95);
        a.add(16);
        a.add(80);
        a.add(80);
        a.add(75);
        a.add(3);
        a.add(25);
        a.add(75);
        a.add(25);
        a.add(31);
        a.add(3);
        a.add(64);
        a.add(16);
        a.add(31);
        
        
        
        List<Integer> a2 = new ArrayList<>();
        a2.add(1);
        a2.add(1);
        a2.add(2);
             
     //   Result.miniMaxSum(arr);
      //  System.out.println(Result.timeConversion("12:00:00AM"));
       // System.out.println(Result.divisibleSumPairs(6, 3, ar));
        
        System.out.println(Result.lonelyinteger(a));
        

       // Result.flippingBits(15);
        System.out.println(Result.flippingBits(2147483647));
        
        
        
    }
}
