#include <string>
#include <iostream>
using namespace std;

static void printHeading(string header)
{
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t                       " << header << "                     \n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n\n";
}

static  string generatePNR()
{
    string pnrNumber;
    int firstFourDigits = 0;
    int secondFourDigits = 0;
   
    firstFourDigits = rand() % 9 + 1; // First Digit should not be Zero
    for (int index = 1; index < 4; index++)
    {
        firstFourDigits = firstFourDigits * 10 + rand() % 10; // generate first 3 digits.

    }
    for (int index = 0; index < 4; index++)
    {
        secondFourDigits = secondFourDigits * 10 + rand() % 10; // generate last 4 digits.

    }
    long randomNumber = firstFourDigits*1000 + secondFourDigits;
    pnrNumber = "PNR" + to_string(randomNumber);
    return pnrNumber;
}

static string  getCurrentDate()
{
    time_t t = time(NULL);
    tm* tPtr = localtime(&t);
    return to_string(tPtr->tm_mday) + "-" + to_string((tPtr->tm_mon) + 1) + "-" + to_string((tPtr->tm_year) + 1900);
}
#pragma once
