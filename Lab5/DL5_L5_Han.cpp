/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 5: Create a bar chart by reading from a .txt file


 +++ Important data abstraction: +++
 All of the temperature data from the file is stored as a vector of tuples.
 Each tuple or "MonthTuple" is composed of 3 elements: (month, low temperature, high temperature).
 It is assumed that the first low-high temperature in the file is the first month and subsequent pairs are ordered.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

//Define file name to open and define a type called MonthTuple
#define fileName "lohiF.txt"
typedef tuple<int, int, int> MonthTuple;

//Prototypes
int getHighTemp(MonthTuple singleMonth);
int getLowTemp(MonthTuple singleMonth);
int getMonth(MonthTuple singleMonth);

int main() {
    //Open file
    ifstream inputFile {fileName};

    if (inputFile) {
        //Print introduction, get first description line from file and print description
        cout << "Jonathan's bar chart:\n";
        string fullLine{};
        getline(inputFile, fullLine);
        cout << fullLine << endl;

        //Create vector containing MonthTuples
        vector <MonthTuple> MonthlyTemperatures;

        //Pull temperature pairs from file and store in MonthlyTemperatures
        int lowTemp{};
        int highTemp{};
        for (int month = 1; inputFile >> lowTemp >> highTemp; month++) {
            MonthlyTemperatures.emplace_back(month, lowTemp, highTemp);
        }

        //Find the highest and lowest values possible for the chart
        //by iterating through each month in MonthlyTemperatures
        int highestTempPossible{-999};
        int lowestTempPossible{999};
        for (auto &singleMonth: MonthlyTemperatures) {
            if (getHighTemp(singleMonth) > highestTempPossible) {
                highestTempPossible = getHighTemp(singleMonth);
            }
            if (getLowTemp(singleMonth) < lowestTempPossible) {
                lowestTempPossible = getLowTemp(singleMonth);
            }
        }

        //Print chart top to bottom starting at the highest temperature possible
        int chartTemp {highestTempPossible};
        while (chartTemp >= lowestTempPossible-1) {
            cout << setw(5) << chartTemp << " F "; //Y-axis legend

            //For each degree Fahrenheit, check if the temperature is between the high and low of each month
            //Print stars if so or empty spaces if not
            for (auto &singleMonth: MonthlyTemperatures) {
                if (chartTemp >= getLowTemp(singleMonth) and chartTemp <= getHighTemp(singleMonth)) {
                    cout << setw(4) <<"**";
                }
                else {
                    cout << setw(4) << ' ';
                }
            }
            cout << endl;
            chartTemp--;
        }

        //Print X-axis legend by iterating through each month and printing the month value
        cout << left << setw(8) << "Temp  F";
        for (auto &singleMonth: MonthlyTemperatures) {
            cout << right << setw(4) << getMonth(singleMonth);
        }
        cout << " Month" << endl;
    }

    //If file doesn't open properly then print error message
    else {
        cout << "Error: " << fileName << " did not open properly!\n";
        cout << "Make sure " << fileName << " is named correctly and is in the same directory.\n";
    }
    inputFile.close();
    return(EXIT_SUCCESS);
}

//Getter functions for a single month
int getHighTemp(MonthTuple singleMonth) { //Get high temp
    return get<2>(singleMonth);
}

int getLowTemp(MonthTuple singleMonth) { //Get low temp
    return get<1>(singleMonth);
}

int getMonth(MonthTuple singleMonth){ // Get month
    return get<0>(singleMonth);
}

/*
TEST OUTPUT:

./DL5_L5_Han
Error: lohiF.txt did not open properly!
Make sure lohiF.txt is named correctly and is in the same directory.
./DL5_L5_Han
Jonathan's bar chart:
Austin Average Monthly low high Temperatures (Fahrenheit) Years 2010 - 2019
  100 F                               **
   99 F                               **
   98 F                           **  **
   97 F                           **  **
   96 F                           **  **
   95 F                           **  **
   94 F                       **  **  **
   93 F                       **  **  **  **
   92 F                       **  **  **  **
   91 F                       **  **  **  **
   90 F                       **  **  **  **
   89 F                       **  **  **  **
   88 F                       **  **  **  **
   87 F                   **  **  **  **  **
   86 F                   **  **  **  **  **
   85 F                   **  **  **  **  **
   84 F                   **  **  **  **  **
   83 F                   **  **  **  **  **  **
   82 F                   **  **  **  **  **  **
   81 F               **  **  **  **  **  **  **
   80 F               **  **  **  **  **  **  **
   79 F               **  **  **  **  **  **  **
   78 F               **  **  **  **  **  **  **
   77 F               **  **  **  **  **  **  **
   76 F               **  **  **  **  **  **  **
   75 F           **  **  **  **          **  **
   74 F           **  **  **  **          **  **
   73 F           **  **  **              **  **
   72 F           **  **  **              **  **  **
   71 F           **  **  **                  **  **
   70 F           **  **  **                  **  **
   69 F           **  **  **                  **  **
   68 F           **  **  **                  **  **
   67 F       **  **  **  **                  **  **
   66 F       **  **  **                      **  **
   65 F       **  **  **                      **  **
   64 F       **  **  **                      **  **  **
   63 F   **  **  **  **                      **  **  **
   62 F   **  **  **  **                      **  **  **
   61 F   **  **  **  **                      **  **  **
   60 F   **  **  **  **                          **  **
   59 F   **  **  **  **                          **  **
   58 F   **  **  **                              **  **
   57 F   **  **  **                              **  **
   56 F   **  **  **                              **  **
   55 F   **  **  **                              **  **
   54 F   **  **  **                              **  **
   53 F   **  **  **                              **  **
   52 F   **  **                                  **  **
   51 F   **  **                                  **  **
   50 F   **  **                                  **  **
   49 F   **  **                                      **
   48 F   **  **                                      **
   47 F   **  **                                      **
   46 F   **  **                                      **
   45 F   **                                          **
   44 F   **                                          **
   43 F   **
   42 F   **
   41 F   **
   40 F
Temp  F    1   2   3   4   5   6   7   8   9  10  11  12 Month

 */