/* Author: Somaiyah Sultani
 * Date: November 6, 2024
 * Description: The program will read a text file, contaning the inventory data of a store,
 * and output the total value of each item in the invetory in a table form, ending with the total value of all items in the inventory. 
 *
 */

// #include <iostream>
// #include <fstream>
// #include <iomanip>
// #include <string>

// using namespace std;

// int main(){

//     /*read the data from the text file.*/
//     ifstream inputFile("inventory.txt");
//     ofstream outputFile("output.txt");

//     if (!inputFile.is_open() || !outputFile.is_open()){
//         cerr << "Error opening file." << std::endl;
//         return 1;
//     }

//     return 0; 
// }

// int main() {
   

//     outputFile << std::setw(15) << "Item" 
//                << std::setw(15) << "Units" 
//                << std::setw(15) << "Unit Cost ($)" 
//                << std::setw(20) << "Total Value ($)" << std::endl;
//     outputFile << std::string(65, '-') << std::endl;

//     InventoryItem item;

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

struct InventoryItem {
    std::string partName;
    int units;
    float price;
};

int main() {
    std::ifstream inputFile("inventory.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    outputFile << std::string(65, '*') << std::endl;
    outputFile << std::internal << "Inventory Report For Jane Doe International Hardware" << std::endl; 
    outputFile << std::string(65, '*') << std::endl; 
    
    outputFile << std::left << std::setw(15) << "Item" 
               << std::left << std::setw(15) << "Units" 
               << std::left << std::setw(15) << "Unit Cost ($)" 
               << std::left << std::setw(20) << "Total Value ($)" << std::endl;
    outputFile << std::string(65, '-') << std::endl;

    InventoryItem item;
    float totalCost = 0.0;

    while (inputFile >> item.partName >> item.units >> item.price) {
        float itemValue = item.units * item.price;
        totalCost += itemValue;

        outputFile << std::left << std::setw(15) << item.partName 
                   << std::internal << std::setw(15) << item.units 
                   << std::setw(15) << std::fixed << std::setprecision(2) << item.price 
                   << std::setw(20) << std::fixed << std::setprecision(2) << itemValue 
                   << std::endl;
    }

    outputFile << std::string(65, '-') << std::endl;
    outputFile << std::left << std::setw(45) << "Total Inventory Cost ($)" 
               << std::right << std::setw(20) << std::fixed << std::setprecision(2) << totalCost << std::endl;

    
   std::ifstream displayFile("output.txt");
    if (displayFile.is_open()) {
        
        std::string line;
        while (std::getline(displayFile, line)) {
            std::cout << line << std::endl;
        }
        displayFile.close();
    } else {
        std::cerr << "Error opening output file for display." << std::endl;
    }
    
    inputFile.close();
    outputFile.close();

    std::cout << "Inventory data processed and written to output.txt" << std::endl;
    return 0;
}