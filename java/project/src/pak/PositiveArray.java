package pak;
import java.util.Arrays;
import java.util.Scanner;

public class PositiveArray {

	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		
		int arrayLength = 8;
		System.out.println("The array length is: " + arrayLength );
		int[] arr = new int[arrayLength];
		
		
		// Accept user input and initialize the array 
		for (int i = 0; i < arr.length; i++) {
			System.out.println("Please enter value for the array:");
			int val = input.nextInt();
			while(val <= 0) {
				System.out.println("Please enter a positive value:");
				val = input.nextInt();
			}
			arr[i] = val;
		}
		
		input.close();
		
		// print array before swapping 
		System.out.println("Before swapping the min max, the array is");
		for(int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
		
		
		
		// Find max and min
		int maxPos = 0;
		int minPos = 0;
		for (int i = 0; i < arr.length; i++) {
			if (arr[i] < arr[minPos]) {
				minPos = i;
			}
			if (arr[i] > arr[maxPos]) {
				maxPos = i;
			}
		}
		// print out max and min
		System.out.println("The max is " + arr[maxPos] + " and its location is " + maxPos);
		System.out.println("The min is " + arr[minPos] + " and its location is " + minPos);
		
		
		
		// swap min and max 
		int temp = arr[minPos];
		arr[minPos] = arr[maxPos];
		arr[maxPos] = temp;
		
		//print out after swap 
		System.out.println("After swapping the min max, the array is");
		for(int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
		
		
		
		// sort array and print out 
		Arrays.sort(arr);
		System.out.print("The array sorted in Ascending order: ");
		for (int i = 0; i < arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
		
		
		
		// Find the median 
		int index = (arr.length-1)/2;
		int remainder = arr.length%2;
		
		if (remainder == 1) {
			System.out.println("The median is: " + arr[index]);
		}
		else {
			System.out.println("The median is: " + (arr[index] + arr[index+1])/2.0);
		}
		

	}

}
