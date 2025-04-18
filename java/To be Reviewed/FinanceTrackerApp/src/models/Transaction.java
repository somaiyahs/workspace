package models;

import java.sql.Date;

public class Transaction {

    /* Constants */
    private static final boolean DEPOSIT = true; 
    private static final boolean WITHDRAW = false;

    /* Instnace Variables */
    private Date date;
    private String merchant;
    private double amount; 
    private Account account; 
    private String category;
    private boolean flow;
    private boolean variability;  
    private String notes;
    //private ArrayList<String> documents;
    //private int importance; 

    /* Data validation needs to be added.  */
    public Transaction(Date date, String merchant, double amount, Account account, boolean flow, String category, boolean variability, String notes){
        this.date = date; 
        this.merchant = merchant; 
        this.amount = amount; 
        this.account = account; 
        this.flow = flow; 
        this.category = category; 
        this.variability = variability;
        this.notes = notes;
    }

    /* Getter methods  */
    public static boolean isDeposit() {
        return DEPOSIT;
    }

    public static boolean isWithdraw() {
        return WITHDRAW;
    }

    public Date getDate() {
        return date;
    }

    public String getMerchant() {
        return merchant;
    }

    public double getAmount() {
        return amount;
    }

    public Account getAccount() {
        return account;
    }

    public String getCategory() {
        return category;
    }

    public boolean isFlow() {
        return flow;
    }

    public boolean isVariability() {
        return variability;
    }

    public String getNotes() {
        return notes;
    }

     /* Setter methods */
    public void setDate(Date date) {
        this.date = date;
    }

    public void setMerchant(String merchant) {
        this.merchant = merchant;
    }

    public void setAmount(double amount) {
        this.amount = amount;
    }

    public void setAccount(Account account) {
        this.account = account;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public void setFlow(boolean flow) {
        this.flow = flow;
    }

    public void setVariability(boolean variability) {
        this.variability = variability;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }

   
    
    
    
}
