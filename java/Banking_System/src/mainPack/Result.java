package mainPack;


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
	    
	    for (int i = 0; i <size - 1; i++){
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



	}

