package bankAccount;

/**
   A bank account has a balance that can be changed by 
   deposits and withdrawals, and earns interest.
 */
public class SavingsAccount
{  
	/**
	 * Private field that stores 
	 * the balance of the account
	 */
	private double balance;
	/**
	 * Private field that stores the rate of the interest 
	 * that the customer earns on her/his balance.
	 */
	private double interestRate;

	/**
	 * Default constructor which constructs a bank account
	 * with a zero balance and zero interest rate.
	 */
	public SavingsAccount()
	{   
		this.balance = 0.0;
		this.interestRate = 0.0;
	}

	/**
	 * Constructs a bank account with a given balance.
	 * @param initialBalance the initial balance
	 */
	public SavingsAccount(double initialBalance, double initialInterestRate)
	{   
		this.balance = initialBalance;
		this.interestRate = initialInterestRate;
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
	 * Increases the balance, adding an interest amount 
	 * at the specified interest rate of the account.
	 */
	public void addInterest() 
	{
		this.balance *= (1.0 + this.interestRate/100.0);
	}   
}