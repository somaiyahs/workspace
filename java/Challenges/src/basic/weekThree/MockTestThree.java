package basic.weekThree;

import java.util.*;

public class MockTestThree {

	/*
     * Complete the 'getTotalX' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER_ARRAY a
     *  2. INTEGER_ARRAY b
     */

    public static int getTotalX(List<Integer> a, List<Integer> b) {
    // Write your code here
    
    int total = 0; 
    Collections.sort(b);
    Collections.sort(a);
    List<Integer> factors = new ArrayList<>();
    
    boolean flag ;
    
    for (int i = a.get(a.size()-1); i <= b.get(0); i++)
    {
        if (b.get(0) % i == 0){
            flag = true;
            for (int j = 1; j < b.size(); j++){
                if (b.get(j)%i != 0){
                    flag = false;
                }
            }
            if(flag){
                factors.add(i);
            }
        }
    }
    
    for(int i = 0; i < factors.size(); i++){
        flag = true; 
        for (int j = 0; j < a.size(); j++){
            if (factors.get(i)%a.get(j) != 0){
                flag = false;
            }
        }
        if(flag){
            total++;
        }
    }
    
    return total;

    }
	public static void main(String[] args) {

		List<Integer> a = new ArrayList<>();
		a.add(3);
		a.add(9);
		a.add(6);

		List<Integer> b = new ArrayList<>();
		b.add(36);
		b.add(72);

		System.out.println(getTotalX(a, b));

	}

}
