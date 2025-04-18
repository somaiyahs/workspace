
#pragma once
#include <string>

using namespace std;

class romanType
{
    private: 
        string romanNumeral;
        int integerValue; 

        int romanToInteger(const string& roman);

    public:

        romanType(const string& roman = "");

        void setRomanNumeral(const string& roman);

        // Get the Roman numeral
        string getRomanNumeral() const;

        int getInetegrValue() const; 

        void printRomanNumeral() const;

        void printIntegerValue() const; 

};