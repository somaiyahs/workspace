package pak;
import java.util.Scanner;

public class Driver {
	public static void main(String[] args){
		
		System.out.println("For 6 customers enter the name and in the next line the balance");
		
		Scanner input = new Scanner(System.in);
		Customer cust[] = new Customer[6];
		for (int i = 0; i < 6; i++) {
			Customer c = new Customer(input.next(), input.nextDouble());
			cust[i] = c;
		}
		input.close();
		double total = 0;
		Customer min = cust[0];
		Customer max = cust[0];
		
		System.out.println("Search for all customers who have less than $150");
		for (int i = 0; i<cust.length; i++) {
			total = cust[i].balance + total;
			if (cust[i].balance < 150) {
				System.out.println(cust[i].name);
			}
			if (min.balance > cust[i].balance) {
				min = cust[i];
			}
			if (max.balance < cust[i].balance) {
				max = cust[i];
			}
			cust[i].addPercentage(15);
			
		} 
		double avg;
		avg = total/cust.length;
		System.out.println("The average balance is: " +avg);
		System.out.println("The customer with the highest balance is: "+max.name);
		System.out.println("The customer with the lowest balance is: "+min.name);
		System.out.println("Show all accounts after a 15% balance increase");
		for (int i = 0; i<cust.length; i++) {
			String name = cust[i].name + " has";
			System.out.printf("%-16s", name);
			System.out.println(cust[i].balance);
		}
	}
}
