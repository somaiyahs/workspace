/* AUTHOR: Somaiyah Sultani
 * DATE: November 14, 2024
 * DESCRIPTION: The program receives a zipcode an input from the user and 
 * prints out a barcode based on the provided zipcode. 
 */


#include <iostream>
#include <string>
#include <cctype> // for isdigit(): checking is a character in a string is a digit

using namespace std; 

/* CONSTANTS */
/* Barcode representation for each digit: 0 -> 9 */
const string BARCODE_PATTERN[10] = {"||:::", ":::||", "::|:|", "::||:", 
    ":|::|", ":|:|:",  ":||::",  "|:::|",  "|::|:", "|:|::"};
/* Multiplier for producing the correction digit.*/
const int MODULUS_BASE = 10;
const int ZIPCODE_LENGTH = 5;


/* The main and the only method of this program. */
int main(){

    /* Declaring and defining variables for the input and output. */
    string zipcode; //Input 
    string barcode = "|"; //Output, containing the initial frame_bar of the barcode.
    int checkDigit; // the correction digit
    int sum = 0; // the sum of all the digits of the zipcode, needed to calculate the correction digit. 

    /*User prompt, asking for an input and storing it, by assigning it to the appropriate variable.*/
    cout << "type your zipcode";
    cin >> zipcode;

    /* INPUT VALIDATION: Checking the length of the input. */
    if (zipcode.length() != 5){
        cerr << "INVALID ZIPCODE: The length of the input provided does not match the requirement." 
             << endl
             << "PLEASE NOTE: A valid zipcode is made up of exactly 5 digits.";
        return 1; 
    }

    /* INPUT VALIDATION: Checking if the input contanins only digits. */
    // for (int i = 0; i < zipcode.at(i); i++){
    //     int digit = zipcode.at(i) - '0';
    //     if(digit < '0' || digit > '9'){
    //         cerr << "INVALID ZIPCODE: The input provided contains non-numerical characters." 
    //          << endl
    //          << "PLEASE NOTE: A valid zipcode is made up of exactly 5 digits.";
    //         return 1;
    //     }
    // }
    
    /* Appending the appropriate partial-barcode according to the zipcode provided.*/
    for (int i = 0; i < zipcode.length(); i++){

        /* Getting the numerical value for each character.*/
        int digit = zipcode.at(i) - '0';
        sum += digit;

        /* Appending the appropriate partial-barcode for the current digit. */
        if (digit == 1){
            barcode.append(ONE);
        }
        else if (digit == 2){
            barcode.append(TWO);
        }
        else if (digit == 3){
            barcode.append(THREE);
        }
        else if (digit == 4){
            barcode.append(FOUR);
        }
        else if (digit == 5){
            barcode.append(FIVE);
        }
        else if (digit == 6){
            barcode.append(SIX);
        }
        else if (digit == 7){
            barcode.append(SEVEN);
        }
        else if (digit == 8){
            barcode.append(EIGHT);
        }
        else if (digit == 9){
            barcode.append(NINE);
        }
        else{
            barcode.append(ZERO);
        }
    }

    /* Calculate the correction digit */
    checkDigit = TEN - (sum % TEN);

    /* Appending the corresponding barcode-representation of the correction digit to the barcode. */
    if (checkDigit == 1){
        barcode.append(ONE);
    }
    else if (checkDigit == 2){
        barcode.append(TWO);
    }
    else if (checkDigit == 3){
        barcode.append(THREE);
    }
    else if (checkDigit == 4){
        barcode.append(FOUR);
    }
    else if (checkDigit == 5){
        barcode.append(FIVE);
    }
    else if (checkDigit == 6){
        barcode.append(SIX);
    }
    else if (checkDigit == 7){
        barcode.append(SEVEN);
    }
    else if (checkDigit == 8){
        barcode.append(EIGHT);
    }
    else if (checkDigit == 9){
        barcode.append(NINE);
    }
    else{
        barcode.append(ZERO);
    }

    /* Adding the ending frame-bar*/
    barcode.append("|");

    cout << barcode << endl;

    return 0; 
}
