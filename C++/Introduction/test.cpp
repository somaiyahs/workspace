#include <iostream>
#include <fstream>

int main() {
    // Define the file name
    std::string filename = "example.txt";

    // Create an ofstream object
    std::ofstream outputFile;

    // Open the file
    outputFile.open(filename);

    if (outputFile.is_open()) {
        // File was successfully opened
        std::cout << "File created successfully.\n";

        // Close the file
        outputFile.close();
    } else {
        // An error occurred while opening the file
        std::cerr << "Error: Unable to create the file.\n";
    }

    return 0;
}