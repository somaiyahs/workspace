package bankAccount;

/**
   A bank account has a balance that can be changed by 
   deposits and withdrawals.
 */
public class BankAccount
{  
	/**
	 * Private field that stores 
	 * the balance of the account
	 */
	private double balance;

	/**
	 * Default constructor which constructs a bank account with a zero balance.
	 */
	public BankAccount()
	{   
		this.balance = 0.0;
	}

	/**
	 * Constructs a bank account with a given balance.
	 * @param initialBalance the initial balance
	 */
	public BankAccount(double initialBalance)
	{   
		this.balance = initialBalance;
	}

	/**
	 * Deposits money into the bank account.
	 * @param amount the amount to deposit
	 */
	public void deposit(double amount)
	{  
		this.balance += amount;
	}

	/**
	 * Withdraws money from the bank account.
	 * @param amount the amount to withdraw
	 */
	public void withdraw(double amount)
	{   
		this.balance -= amount;
	}

	/**
	 * Gets the current balance of the bank account.
	 * @return the current balance
	 */
	public double getBalance()
	{   
		return this.balance;
	}

	/**
	 * Adds interest to the account at the given rate
	 * @param rate
	 */
	public void addInterest(double rate) 
	{
		this.balance *= (1.0+0.01*rate);
	}

}

