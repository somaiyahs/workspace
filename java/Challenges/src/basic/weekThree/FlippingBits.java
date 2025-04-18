package basic;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class FlippingBits {
	
	/* The function is expected to return a LONG_INTEGER.
		     * The function accepts LONG_INTEGER n as parameter.
		     */
	
	
	
	public static long flippingBits(long n) {
		
		long num = -1;
		
		/* Step1: Change dec to bin *****************/
		int[] bits = new int[32]; // to hold the bits from the least to the most significant
        
		// Initializing the array
        for (int i = 0; i < bits.length; i++){
            bits[i] = 0;
        }
        
        long q = n; // quotient in the division process
        
        for (int i = 0; q != 0; i++) {
        	
        	if ((q%2) == 1) {
        		bits[i] = 1; 
        	}
        	q /= 2;
        }
        
        /* Step2: Flip the bits *********************/
        for (int i = 0; i < bits.length; i++) {
        	if(bits[i] == 1) {
        		bits[i] = 0;
        	}
        	else {
        		bits[i] = 1;
        	}
        }
        
        /* Step3: Change bin to dec ***************/
        long power = 1;
        for (int i = 0; i < bits.length; i++) {
        	num += bits[i] * power;
        	power *= 2;
        }
        
		    	
		return num;
	}

	
	public static int countingValleys(String path) {
		 boolean sea = true;
		    int totV = 0;
		    int totM = 0;
		    int val = 0;
		    int mount = 0;
		    
		    for (int i = 0; i < path.length(); i++){
		        
		    	if (sea && path.charAt(i) == 'D') {
		    		val--;
		    		sea = false;
		    	}
		    	else if (sea && path.charAt(i) == 'U') {
		    		mount++;
		    		sea = false;
		    	}
		    	else if(val < 0) {
		    		if (path.charAt(i) == 'D') {
		    			val--;
		    		}
		    		else {
		    			val++;
		    			if(val == 0) {
		    				totV++;
		    				sea = true;
		    			}
		    		}
		    	}
		    	else if (mount > 0) {
		    		if (path.charAt(i) == 'U') {
		    			mount++;
		    		}
		    		else {
		    			mount--;
		    			if(mount == 0) {
		    				totM++;
		    				sea = true;
		    			}
		    		}
		    	}
		    	
		    }
		    
		    
		    return totV;

	}
	
	public static String pangrams(String s) {
	    // Write your code here
	    String[] alphabet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
	    for (String a: alphabet){
	        if (!s.toLowerCase().contains(a)){
	            return "not pangram";
	        }
	    }
	    
	    return "pangram";

	    }
	
	
	 public static int marsExploration(String s) {
		    // Write your code here
		    int changed = 0;
		    
		    for (int i = 0; i <s.length(); i+=3){
		        if(!s.substring(i, i+3).equals("SOS")){
		            if(s.charAt(i) != 'S'){
		                changed++;
		            }
		            if(s.charAt(i+1) != 'O'){
		                changed++;
		            }
		            if(s.charAt(i+2) != 'S'){
		                changed++;
		            }
		        }
		    }
		    return changed;
		    }

	 public static void reverse(int[] arr) {
		 int n = arr.length;
		 
			 if (arr[0] < arr[n-1] ){
				for(int j = 0; j < n/2; j++) {
				 int temp = arr[j];
				 arr[j] = arr[n-1-j];
				 arr[n-1-j] = temp; 
			 	}
			 } 
		 }
	 
	 
	 public static int sum(int[][] m) {
		
		
		 int max = 0; 
		 int n = m.length;
		 
//		 for (int index = 0; index < n; index++) {
//			 for (int index2 = 0; index2 < n; index2++) {
//				 int sum = 0;
//		 for (int i = 0; i < n; i++) {
//			 for (int j = 0; j < n; j++) {
//				 if(m[0][j] < m[n-1][j]) {
//					for (int k = 0; k < n/2; k++) {
//						int temp = m[k][j];
//						m[k][j] = m[n-1-k][j]; 
//						m[n-1-k][j] = temp;
//					}
//				 }
//			 }
//		 }
//		 
//		 
//		 for (int i = 0; i < n/2; i++){
//			 
//		 }

		 for (int i = 0, sum = 0; i < n; i++) {
			 
			 for (int j = 0; j < n; j++) {
				 reverse(m[i]);
				 reverse(m[j]);
			 }
			 for (int j = 0; j < n/2; j++) {
				 sum += m[i][j];
			 }
			 if(max < sum) {
				 max = sum;
			 } 
		 }
		 
		
		 
		 for(int i = 0; i < n; i++) {
			 System.out.print("Row" + i + ": ");
			 for(int j = 0; j <n; j++) {
			 System.out.print(m[i][j] + " ");
			 }
			 System.out.println();
		 }
		 
		 for (int i = 0; i < n; i++) {
			 System.out.print("Column" + i + ": ");
			 for (int j = 0; j < n; j++) {
				 System.out.print(m[j][i] + " ");
			 }
			 System.out.println();
		 }
 
		 return max;
		 
	 }
	
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
	//	System.out.println(flippingBits(2147483647));
	//	System.out.println(flippingBits(0));
	//	System.out.println(flippingBits(0));
		
		//System.out.println(countingValleys("DDUUDDUDUUUD"));
		List<Integer> a1 = new ArrayList<>();
		a1.add(1);
		a1.add(2);
		a1.add(3);
		a1.add(4);
		
		List<Integer> a2 = new ArrayList<>();
		a2.add(4);
		a2.add(5);
		a2.add(6);
		a2.add(7);
		
		List<Integer> a3 = new ArrayList<>();
		a3.add(9);
		a3.add(3);
		a3.add(20);
		a3.add(1);
		
		List<Integer> a4 = new ArrayList<>();
		a4.add(12);
		a4.add(5);
		a4.add(9);
		a4.add(7);
		
		List<List<Integer>> a = new ArrayList<>();
		a.add(a1);
		a.add(a2);
		a.add(a3);
		a.add(a4);
		
		int[][] m = {{112, 42, 83, 119}, {56,125, 56, 49}, {15, 78, 101, 43}, {62, 98, 114, 108}};
		
		System.out.println(sum(m));

	}

}
