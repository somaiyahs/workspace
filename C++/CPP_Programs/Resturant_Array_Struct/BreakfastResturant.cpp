#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Struct for menu items
struct menuItemType {
    string itemName;
    double itemPrice;
};

// Function prototypes
void getData(menuItemType menuList[], int size);
void showMenu(menuItemType menuList[], int size);
void printCheck(menuItemType menuList[], int size, int selection[], int selectionSize);

int main() {
    
    // Defining local variables
    const int MENU_SIZE = 8;
    menuItemType menuList[MENU_SIZE];
    getData(menuList, MENU_SIZE);

    cout << "Welcome to Johnny's Restaurant" << endl;

    showMenu(menuList, MENU_SIZE);

    int selection[MENU_SIZE] = {0}; // Array to store selected item indexes
    int selectionCount = 0;

    while (true) {
        cout << "Enter the item number to select (or -1 to finish): ";
        int choice;
        cin >> choice;

        if (choice == -1) {
            break;
        } else if (choice >= 1 && choice <= MENU_SIZE) {
            selection[selectionCount++] = choice - 1;
        } else {
            cout << "Invalid selection. Please try again." << endl;
        }
    }

    printCheck(menuList, MENU_SIZE, selection, selectionCount);

    return 0;
}

void getData(menuItemType menuList[], int size) {
    menuList[0].itemName = "Plain Egg";
    menuList[0].itemPrice = 1.45;

    menuList[1].itemName = "Bacon and Egg";
    menuList[1].itemPrice = 2.45;

    menuList[2].itemName = "Muffin";
    menuList[2].itemPrice = 0.99;

    menuList[3].itemName = "French Toast";
    menuList[3].itemPrice = 1.99;

    menuList[4].itemName = "Fruit Basket";
    menuList[4].itemPrice = 2.49;

    menuList[5].itemName = "Cereal";
    menuList[5].itemPrice = 0.69;

    menuList[6].itemName = "Coffee";
    menuList[6].itemPrice = 0.50;

    menuList[7].itemName = "Tea";
    menuList[7].itemPrice = 0.75;
}


void showMenu(menuItemType menuList[], int size) {
    cout << "Menu:" << endl;
    for (int i = 0; i < menuList; i++) {
        cout << setw(2) << i + 1 << ". " << left << setw(20) << menuList[i].itemName
             << "$" << fixed << setprecision(2) << menuList[i].itemPrice << endl;
    }
}

void printCheck(menuItemType menuList[], int size, int selection[], int selectionSize) {
    double total = 0.0;

    cout << "\nYour order:" << endl;
    for (int i = 0; i < selectionSize; i++) {
        int itemIndex = selection[i];
        cout << left << setw(20) << menuList[itemIndex].itemName
             << "$" << fixed << setprecision(2) << menuList[itemIndex].itemPrice << endl;
        total += menuList[itemIndex].itemPrice;
    }

    double tax = total * 0.05;
    double amountDue = total + tax;

    cout << left << setw(20) << "Tax" << "$" << fixed << setprecision(2) << tax << endl;
    cout << left << setw(20) << "Amount Due" << "$" << fixed << setprecision(2) << amountDue << endl;
}
