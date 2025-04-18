package basic.weekThree;

import java.util.Collections;
import java.util.List;

/*
 * There is a large pile of socks that must be paired by color. Given an array of integers representing the color of each sock, determine how many pairs of socks with matching colors there are.
Example 
 

There is one pair of color  and one of color . There are three odd socks left, one of each color. The number of pairs is .
Function Description
Complete the sockMerchant function in the editor below.
sockMerchant has the following parameter(s):
int n: the number of socks in the pile
int ar[n]: the colors of each sock
Returns
int: the number of pairs
Input Format
The first line contains an integer , the number of socks represented in . 
The second line contains  space-separated integers, , the colors of the socks in the pile.
Constraints

 where 
Sample Input
STDIN                       Function
-----                       --------
9                           n = 9
10 20 20 10 10 30 50 10 20  ar = [10, 20, 20, 10, 10, 30, 50, 10, 20]
Sample Output
3
 */
public class SalesByMatch {
	
    /*
     * Complete the 'sockMerchant' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER n
     *  2. INTEGER_ARRAY ar
     */

    public static int sockRecursion(int n, List<Integer> ar) {
    // Write your code here
    
    Collections.sort(ar);
    int total = 0;
    //base case
    if(ar.size() < 2){
        return 0; 
    }
    int lastIndex = ar.lastIndexOf(ar.get(0));
    if(lastIndex == 0){
        total += sockRecursion(n-1, ar.subList(1, n));
    }
    else if(lastIndex%2 == 1){
        total += ((lastIndex+1)/2) + sockRecursion(n-1-lastIndex, ar.subList(lastIndex+1, n));
    }
    else{
        total += (lastIndex/2) + sockRecursion(n-1-lastIndex, ar.subList(lastIndex+1, n));
    }

    return total;
    }
    
    public static int sockIteration(int n, List<Integer> ar) {
    	
    	int total = 0;
    	boolean pair = false;
    	
    	if (n > 2) {
    		Collections.sort(ar);
    	
    		for (int i = 1; i < n; i++) {
    		
    			if (ar.get(i) == ar.get(i-1) && !pair) {
    				total++;
    				pair = true;
    			}
    			else{
    				pair = false;
    			}
    		
    		}
    	}
    	
    	return total;
    
    }
    
    



	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
