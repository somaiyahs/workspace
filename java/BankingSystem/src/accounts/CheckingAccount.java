package accounts;

public class CheckingAccount extends BankAccount{
	
	/***************** Constants ********************/
	
	/*****************  Attributes ******************/
	//private final long accountNumber;  // the account number must be 12 digits long
	private String firstName;
	private String lastName;
	private String address; // it needs to follow certain pattern. 
	private double balance;
	private String governmentID;
	private int pinNumber;
	
	
	/*************** Constructors ********************/
	
	/**
	 * First Constructor 
	 */
	public CheckingAccount(String firstName, String lastName, String address,
			double balance, String governmentID, int pinNumber){
		
		super(governmentID, governmentID, governmentID, balance, governmentID, pinNumber);
		
	}


	/**
	 * Second Constructor
	 * default constructor 
	 */
	
	public CheckingAccount(String firstName, 
			String lastName, String address, String governmentID, int pinNumber) {
		this(firstName, lastName, address, 0.0, governmentID, pinNumber);
	}
	
	
	
	
	
	/************************** Methods *********************************/
	
	/*** accessors ***/
	
	
	
	/**
	 * 
	 * @return first name of the account holder
	 */
	public String getFirstName() {
		return this.firstName;
	}
	
	
	public String getLastName() {
		return this.lastName;
	}
	
	
	public String getAddress() {
		return this.address;
	}
	
	
	public double getBalance() {
		return this.balance;
	}
	
	public String getID() {
		return this.governmentID;
	}
	
	public int getPinNumber() {
		return this.pinNumber;
	}
	
	
	
	
	
	
	
	/*** Mutators ***/
	
	
	

	
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}


	public void setLastName(String lastName) {
		this.lastName = lastName;
	}


	public void setAddress(String address) {
		this.address = address;
	}


	public void setBalance(double balance) {
		this.balance = balance;
	}


	public void setGovernmentID(String governmentID) {
		this.governmentID = governmentID;
	}


	public void setPinNumber(int pinNumber) {
		this.pinNumber = pinNumber;
	}


	/**** Others methods ***/
	/**
	 * adds the provided amount to the current balance and return the new balance.
	 * @param amount
	 * @return the new balance
	 */
	public double deposit(double amount) {
		this.balance += amount;
		return this.getBalance();
	}
	/**
	 * subtracts the provided amount from the balance and return the remaining balance.
	 * @param amount
	 * @return the remaining balance 
	 */
	public double withdraw(double amount) {
		
		this.balance -= amount;
		return this.getBalance();
	}
	
	
	public void transferTo(CheckingAccount acc, double amount) {
		this.withdraw(amount);
		acc.deposit(amount);
	}

}
