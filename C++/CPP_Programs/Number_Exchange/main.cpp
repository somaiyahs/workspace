

#include <iostream>
#include "romanType.h"

using namespace std; 

int main(){
    //test cases 
    string testCases[] = {"MCXIV", "CCCLIX", "MDCLXVI"};

    for (const string& testCase : testCases){
        romanType romanNumber(testCase);

        cout << "Testing Roman numeral: " << testCase << endl;
        romanNumber.printRomanNumeral();
        romanNumber.printIntegerValue();
        cout << endl;
    }

    return 0;
}