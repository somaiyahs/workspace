import java.util.ArrayList;

/**
 * Shopping class 
 */

 public class Shopping{

    /******************** Attributes/Instance Variables ***********/
    List<String> shoppingList;
    List<String> availableItems;

    /******************** Constructors  ***********/
    public Shopping(){
        this.shoppingList = new ArrayList<>();
        this.availableItems = new ArrayList<>();
    }

    /******************** Methods ***********/
    public void addAvailableItems(String a){

    }

    public void addShoppingList(){
        // printout the available items for user to pick from 
        for (String s: this.availableItems){
            System.out.println(s);
        }

        

        this.shoppingList(item);
    }

 }