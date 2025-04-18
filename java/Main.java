import java.util.Scanner;
public class Main{

	public static void main(String[] args){

	System.out.println("Please type something!");
	Scanner input = new Scanner(System.in);
	String something = input.next();
	String second = input.next();	
	System.out.println(something);
	System.out.println(second);
	}
}
