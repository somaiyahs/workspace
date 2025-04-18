package introduction;

import java.lang.reflect.Array;

public class ArrayPractice {
	
	public static void main(String[] args) {
		
		/* To create an array:
		*  dataType[] nameOfArray = {data1, data2, ..., dataN};
		**/
		int[] numbers = {94, 123, 87, 4, -3};
		String[] words = {"John", "Jane", "Adam", "Ava"};
		
		/*
		 * To get an element from the array;
		 * 1- Could use the Array class)
		 * 			int thirdInt = Array.getInt(numbers, 2);
		 * 2- access the element directly from "our" array
		 */
		int second = numbers[1];
		String secondWord = words[1];
		
		
		/*
		 * To change the value of an element from the array;
		 * 1- Could use the Array class
		 * 			Array.setInt(numbers, 2, -65);
		 * 2- update the element directly from "our" array
		 */
		numbers[1] = 98;
		words[1] = "Changed";
		
	
		/*
		 * to find the number of the elements in the array 
		 * 1- Could use the Array class
		 * 			int lengthOfNumbers = Array.getLength(numbers);
		 * 2- find without the help of Array class
		 */
		int numbersLen = numbers.length;
		int wordsLen = words.length;
		
		for(int i = 0; i < words.length; i++) {
			System.out.println(words[i]);
		}
	}

}
