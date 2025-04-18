package models;

public class Account {

    /* Constants */
    private static final int DEBIT = 1;
    private static final int CREDIT = 0; 

    private String name;
    private double balance;
    private int type;

    public Account(String name, double balance, int type) {
        this.name = name;
        this.balance = balance;
        this.setType(type);
    }

    /* Getter methods  */
    public String getName() {
        return name;
    }

    public double getBalance() {
        return balance;
    }

    public int getType(){
        return this.type;
    }

    /* Setter methods */
    public void setName(String name) {
        this.name = name;
    }

    public void setBalance(double balance) {
        this.balance = balance;
    } 

    public void setType(int type){
        if (type == DEBIT || type == CREDIT ){
            this.type = type;
        } 
        else{
            System.err.println("Invalid Option: type");
        }
    }

    public boolean isAsset(){
        if (this.getType() == Account.DEBIT){
            return true;
        }
        else {
            return false;
        }
    }

    
    
    
    
    
    
    
}
