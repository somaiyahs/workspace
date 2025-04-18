package basic.weekThree;

import java.util.List;

/*
 * Given an array of bird sightings where every element represents a bird type id, determine the id of the most frequently sighted type. If more than 1 type has been spotted that maximum amount, return the smallest of their ids.
Example 
arr = [1,1,2,2,3]

There are two each of types 1 and 2, and one sighting of type 3. Pick the lower of the two types seen twice: type 1.
Function Description
Complete the migratoryBirds function in the editor below.
migratoryBirds has the following parameter(s):
int arr[n]: the types of birds sighted
Returns
int: the lowest type id of the most frequently sighted birds
Input Format
The first line contains an integer, , the size of . 
The second line describes  as  space-separated integers, each a type number of the bird sighted.
Constraints
5 <= n <= 2 * 10^5

It is guaranteed that each type is 1, 2, 3, 4, or 5.
 */

public class MigratoryBirds {
	
	/* Complete the 'migratoryBirds' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts INTEGER_ARRAY arr as parameter.
     */

    public static int migratoryBirds(List<Integer> arr) {
    // Write your code here
    
    int id = 0;
    int max = 0;
    
    int[] freq = {0, 0, 0, 0, 0};
    
    for (int x: arr){
        freq[x-1] += 1;
    }
    
    for (int i = 0; i < freq.length; i++){
        if( max < freq[i]){
            max = freq[i];
            id = i+1;
        }
    }
    
    return id;

    }



	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
