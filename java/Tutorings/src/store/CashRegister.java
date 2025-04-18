package store;

public class CashRegister
{
	/**
	 * Stores the rate of the sale tax 
	 */
	private double taxRate;
	/**
	 * total cost of the purchase 
	 */
	private double purchase;
	/**
	 * total cost of the taxable purchases
	 */
	private double taxablePurchase;
	/**
	 * payment received for the current purchase 
	 */
	private double payment;
	/**
	 * 	List of all the items in the current purchase
	 */
	private String purchases;
	/**
	 * Total number of transactions
	 */
	private int transactionCount;
	/**
	 * total amount of all the sales
	 */
	private double totalSale;

	/**
	 * Constructs a CashRegister object with the given tax rate.
	 * @param rate
	 */
	public CashRegister(double rate)
	{
		this.taxRate = rate;
		this.purchase = 0.0;
		this.payment = 0.0;
		this.purchases = "";
		this.transactionCount = 0;
		this.totalSale = 0.0;
	}

	/**
	 * Records the purchase by adding the amount 
	 * to the total purchase amount 
	 * and stores the amount in the list of purchases
	 * @param amount
	 */
	public void recordPurchase(double amount)
	{
		/* adding the amount to the total */
		this.purchase += amount;
		/* storing the amount in the list of the purchases */
		this.purchases = purchases.concat("$" + String.valueOf(amount) + "\n");
	}

	/**
	 * Records the taxable purchases by recording the purchase
	 * and adding the amount to the total of the taxable purchases.
	 * @param amount
	 */
	public void recordTaxablePurchase(double amount)
	{
		/* adding the amount to the total of the taxable purchases */
		this.taxablePurchase += amount;
		/* recording the purchase */
		this.recordPurchase(amount);
	}

	/**
	 * Receives the payment by adding the given amount
	 * to the total of the payments made.
	 * @param amount
	 */
	public void receivePayment(double amount)
	{
		/* receiving the payment */
		this.payment += amount;
	}

	/**
	 * Calculates the total tax of the purchase
	 * and returns the sale tax.
	 * @return sale tax of the purchase 
	 */
	public double getSalesTax()
	{
		return this.taxablePurchase * taxRate / 100;
	}

	/**
	 * Calculates the difference of the total cost 
	 * of the purchase and the payments received, 
	 * and it returns that difference to be paid back
	 * to the customer. I also sets all the fields 
	 * of the purchase to their default values. 
	 * @return change to be paid back 
	 */
	public double giveChange()
	{   
		/* Find the total cost of the purchase */
		double cost = this.purchase - this.getSalesTax();

		/* Calculating the change to be paid back */
		double change = this.payment - cost;

		/* Adding the amount of this purchase to the total sale */
		this.totalSale += cost;

		/* incrementing the transaction count by 1*/
		this.transactionCount++;
		
		/* Setting the purchase, taxablePurchase 
		 * and payment fields to their default values.
		 */
		this.purchase = 0.0;
		this.taxablePurchase = 0.0;
		this.payment = 0.0;

		return change;
	}

	/**
	 * Returns the total sale of the cash register 
	 * @return total sale 
	 */
	public double getSalesTotal() {
		return this.totalSale;
	}
	
	/**
	 * Returns the total number of the transaction of the cash register
	 * @return total number of transactions
	 */
	public int getSalesCount() {
		return this.transactionCount;
	}
	
	/**
	 * It set the total sale and total number of transactions to zero
	 */
	public void reset() {
		this.transactionCount = 0;
		this.totalSale = 0.0;
	}
	/**
	 * Displays the total amount of the purchase
	 * and the list of the amounts in that purchase.
	 */
	public void printReciept()
	{
		System.out.print(purchases);
		System.out.println(purchase);
	}
}
