package bankAccount;

/**
   A class to test the BankAccount class.
 */
public class BankAccountTester
{
	/**
      Tests the methods of the BankAccount class.
      @param args not used
	 */
	public static void main(String[] args)
	{
		/* Testing the default constructor */
		BankAccount harrysChecking = new BankAccount();

		/* Testing the deposit method */
		harrysChecking.deposit(2000);

		/* Testing the withdraw method */
		harrysChecking.withdraw(500);

		/* Displaying the actual balance */
		System.out.println("Actual_1: " + harrysChecking.getBalance());

		/* Displaying the expected balance */
		System.out.println("Expected_1: 1500.0"); 

		/* Creating an empty line between the test result of the last account
		 * and the next account for readability 
		 */
		System.out.println(); 

		/* Testing the constructor with an initial balance */
		BankAccount momsSavings = new BankAccount(1000);

		/* Testing addInterest method */
		momsSavings.addInterest(10);

		/* Display the actual balance of momsSavings */
		System.out.println("Actual_2: " + momsSavings.getBalance());

		/* Displays the expected balance of momsSavings */
		System.out.println("Expected_2: 1100.0");
	}
}