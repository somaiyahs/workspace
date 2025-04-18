Questions:
Write a program in C++ to help a local restaurant automate its breakfast building system. The program should do the following:
a. "Show the customer the different breakfast items offered by the restaurant 
b. Allow the customer to select more than one item from the menu
c.Calculate and print the bill.
Assume that the restaurant offers the following breakfast items ( the price of each item is shown to the right of the item):
Plain Egg $1.4s 
Bacon and Egg 92.45 
Muffin $0.99
French Toast $1.99
Fruit Basket $2.49 
Cereal $0.69 
Coffee $0.50
Tea $0.75
Use an array, menulist, of the struct menuItemTvpe. Your program must contaln at least following functions:
- Function getData: This function loads the data into the array menulist.
- Function showMenu: This function shows the different it offered by the restaurant and tells the user how to select the items
- Function printCheck: This function calculates and prints the check. (Note that the billing amount should include a 5% tax.)
A sampleoutput is:
Welcome to Johnny's Restaurant
Bacon and Egg        $2.45
Muffin                       $0.99
Coffee                      $0.50
Tax                            $0.20
Amount Due            $4.14

Format your output with two decimal places. The name of each item in the output must be left justified. You may assume that the user selects only one item of a particular type.



How it works:
getData: Loads the menu items and prices into an array.
showMenu: Displays the menu items and their prices.
printCheck: Calculates the total price, adds a 5% tax, and displays the receipt.

Sample output
Welcome to Johnny's Restaurant
Menu:
 1. Plain Egg           $1.45
 2. Bacon and Egg       $2.45
 3. Muffin              $0.99
 4. French Toast        $1.99
 5. Fruit Basket        $2.49
 6. Cereal              $0.69
 7. Coffee              $0.50
 8. Tea                 $0.75
Enter the item number to select (or -1 to finish): 2
Enter the item number to select (or -1 to finish): 3
Enter the item number to select (or -1 to finish): 7
Enter the item number to select (or -1 to finish): -1

Your order:
Bacon and Egg       $2.45
Muffin              $0.99
Coffee              $0.50
Tax                 $0.20
Amount Due          $4.14
