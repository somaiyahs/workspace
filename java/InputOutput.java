import java.util.Scanner;

public class InputOutput{


	public static void main(String[] args){

	System.out.println("Please enter your input: ");

	Scanner input = new Scanner(System.in);
	
	String userWord = input.next();

	System.out.println(userWord);
	String userSentence = input.nextLine();

	System.out.println(userSentence);
	
	}
}
