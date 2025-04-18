import java.util.ArrayList;

import models.Account;
import models.Transaction;

public class Finance {

    private static final int DEBIT = 1;
    private static final int CREDIT = 0; 


        private ArrayList<Account> accounts;
        private ArrayList<Transaction> transactions; 
        private ArrayList<String> categories; 
        private double asset;
        private double debt; 
    
    private Finance(){
        this.accounts = new ArrayList<>();
        this.transactions = new ArrayList<>();
        this.categories = new ArrayList<>();
        this.asset = 0.0;
        this.debt = 0.0; 
    }
    
    public boolean addAccount(Account account){
        if(account.getType() == DEBIT){
            this.setAsset(account.getBalance());
        } else {
            this.setDebt(account.getBalance());
        }
        return accounts.add(account);
    }

    public boolean addTransaction(Transaction transaction){
       
        int index = this.accounts.indexOf(transaction.getAccount());

        Account acc = this.accounts.get(index);
        
        /* updating the debt/asset of the user's Finance */
        if (acc.isAsset()){
            this.setAsset(transaction.getAmount());
        } else {
            this.setDebt(transaction.getAmount());
        }

        /* updating the balance of the account
         * meybe it should be updateBalance instead of setBalance 
         */
        acc.setBalance(transaction.getAmount());

        // Adding the transaction to the database. 
        // Maybe the transaction should be added to its own account. 
        return transactions.add(transaction);
    }

    public boolean addCategory(String category){
        return categories.add(category);
    }

    public double getAsset(){
        return this.asset;
    }

    public double getDebt(){
        return this.debt;
    }

    private void setAsset(double amount){
        this.asset += amount;
    }

    private void setDebt(double amount){
        this.debt += debt;
    }

}
