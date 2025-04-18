package introduction;

import java.util.Scanner;

public class Main {

	public static void main(String[] Args) {
		
		/*
		 * while(condition){
		 *  body of the loop
		 *  }
		 */
		// create a scanner object to read the user's input 
		Scanner scan = new Scanner(System.in);
		// condition of the while loop 
		boolean condition = false;
		
	
		while(condition) {
			System.out.println("this will not be printed!");		
		}
		
		System.out.println("The while loop has ended!");
		
		do {
			System.out.println("this will be printed!");
		}while(condition);

		System.out.println("The do-while loop has ended!");
	
		
		
		
		
		
		
		
		
		
		
		
		// Print numbers 1 to 10 
//		for(int num = 1; num <= 10; num++) {
//			System.out.print(num + ", ");
//		}
//		
//		System.out.println();
		
		
//		String str = "To be printed!";
//		for(int i = 0; i < str.length(); i++) {
//			
//			System.out.print(str.charAt(i) + ", ");
//		}
//		System.out.println();
//		
		
	//	System.out.println("The for loop result:");
		
//		for(int i = str.length()-1; i >= 0; i--) {
//			
//			System.out.print(str.charAt(i) + ", ");
//		}
//		System.out.println();
//		
//		
//		System.out.println("The while loop result:");
//		int i = str.length()-1;
//		while(i >= 0) {
//			System.out.print(str.charAt(i) + ", ");
//			i--;
//		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//		
		// print the numbers 1 to 10 
//		System.out.println("while loop!");
//		int num = 1; 
//		while(num <= 10) {
//			System.out.print(num + ", ");
//			num++;
//		}
//		System.out.println();
//		System.out.println("For loop!");
//		
//		for(int i = 1; i <= 10; i++) {
//			System.out.print(i + ", ");
//		}
//		System.out.println();
//		
//		Scanner scan = new Scanner(System.in);
//		boolean condition = true;
//		for(; condition;) {
//			System.out.println("Do you want to end the loop?");
//			String input = scan.next();
//			if (input.equals("YES")) {
//				condition = false;
//			}
//		}
	
	}

}
