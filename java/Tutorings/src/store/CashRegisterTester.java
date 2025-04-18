package store;

/**
   A class to test the CashRegister class.
*/
public class CashRegisterTester
{
   public static void main(String[] args)
   {
	   /* creating a cash register with 
	    * 5% sales tax on taxable purchases. */
      CashRegister register = new CashRegister(5);

      /* Adding a taxable purchase */
      register.recordTaxablePurchase(10);
      /* Recording the first item to the purchase */
      register.recordPurchase(29.50);
      /* Recording the second item to the purchase */
      register.recordPurchase(9.25);
      /* Receiving a payment for the purchase */
      register.receivePayment(50);

      /* Calculating the customer's change */
      double change = register.giveChange();

      /* Displaying the actual value of the change */
      System.out.println("Actual: " + change);  
      /* Displaying the expected value of the change */
      System.out.println("Expected: 0.75");          
   }
}

