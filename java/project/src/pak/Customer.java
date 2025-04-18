package pak;
public class Customer {

	public String name;
	public double balance;
	
	public Customer(String name, double balance) {
		this.name = name;
		this.balance = balance;
	}
	public String toString() {
		String cust;
		cust = name + " " + balance;
		return cust;
	}
	public void addPercentage(double percentage){
	
		balance += balance * percentage/100;
		
	}
}