package bankAccount;

public class SavingsAccountTester {

	/**
    Tests the methods of the BankAccount class.
    @param args not used
	 */
	 public static void main(String[] args)
	 {
		/* Testing the constructor with given the balance and interest rate*/
	    SavingsAccount savingsTest = new SavingsAccount(1000,10);
	    
	    /* Testing addInterest method */
	    savingsTest.addInterest();
	    
	    /* Displaying the actual balance */
	    System.out.println("Actual: " + savingsTest.getBalance());
	    
	    /* Displaying the expected balance */
	    System.out.println("Expected: 1100.0");
	 }
	
}
