package introduction;

import java.util.Scanner;

public class If_condition {

	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		System.out.println("Please type a number");
		
		int n = input.nextInt();
		input.close();
		if(n < 0) {
			// execute the body
			System.out.println("The number is negative");
		}
		else if(n > 0) {
			System.out.println("The number is posititve.");
		}
		else{
			System.out.println("The number is zero.");
		}
		
	}

}
