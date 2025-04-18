package pak;
import java.util.Scanner;

public class Queens {

	public static void main(String[] args) {
		
		Scanner input = new Scanner(System.in);
		
		int size = 10;
		char[][] queen = new char[size][size];
		// initializing the array 
		for(int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				queen[i][j] = '.';
			}
		}
		
		// getting user input and updating the provided indices 
		for(int i = 0; i < 10; i++) {
			System.out.println("Please enter column to put queen");
			queen[i][input.nextInt()] = 'Q';
		}
		
		input.close();
		
		// Printing out the array
		for(int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				System.out.print(queen[i][j]);
			}
			System.out.println();
		}
		

	}

}
