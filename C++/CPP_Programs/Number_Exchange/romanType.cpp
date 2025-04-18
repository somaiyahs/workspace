// include the class definition from the header file 
#include "romanType.h"

// includes the library for mapping numeral characters to integer values 
#include <unordered_map>

// 
#include <iostream>

using namespace std;

// 

int romanType::romanToInteger(const string& roman){
    
    unordered_map<char, int> romanValues;
romanValues['M'] = 1000;
romanValues['D'] = 500;
romanValues['C'] = 100;
romanValues['L'] = 50;
romanValues['X'] = 10;
romanValues['V'] = 5;
romanValues['I'] = 1;

    int total = 0;
    for (size_t i = 0; i < roman.length(); i++){
        if (i < roman.length()-1 &&romanValues[roman[i]] < romanValues[roman[i+1]]){
            total -=romanValues[roman[i]];
        } else{
            total +=romanValues[roman[i]];
        }
    }
    return total;
}

romanType::romanType(const string& roman){
    setRomanNumeral(roman);
}

//set the Roman numeral and calculate the integer value
void romanType::setRomanNumeral(const string& roman){
    romanNumeral = roman;
    integerValue = romanToInteger(roman);
}

// Get roman numeral
string romanType::getRomanNumeral() const{
    return romanNumeral; 
}

// Get the integer value
int romanType::getInetegrValue() const{
    return integerValue;
}

//print the roman numeral 
void romanType::printRomanNumeral() const {
    cout << "Roman numeral: " << romanNumeral << endl;
}

// print the integer value
void romanType::printIntegerValue() const {
    cout << "Integer value: " << integerValue << endl;
}

