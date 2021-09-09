/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 1: Perform multiple distance conversions for centimeter, inch, or feet until user quits
*/

#include <iostream>
#include <iomanip>
using namespace std;

const double CENTIMETERS_IN_INCH {2.54};
const int INCHES_IN_FOOT {12};

// Prototypes
int check_validity();

int main()
{
    int value {};
    while (true)
    {
        cout << "Welcome! This program will allow you to convert distances!\n";
        cout << "What is your starting unit? ";
        cout << "c)entimeter, i)nch, f)eet, or q)uit : ";
        char unit {};
        cin >> unit;

        //Case c: calculate inches and feet
        if (unit == 'C' || unit == 'c')
        {
            cout << "Distance in centimeters(whole number)? ";
            //Get user input and validate input
            value = check_validity();

            //Convert and output
            cout << "\n  Integer:    " << "centimeters=" << left << setw(10) << value << "inches="
                << setw(10) << static_cast<int>(value/CENTIMETERS_IN_INCH) << "feet=" << static_cast<int>(value/CENTIMETERS_IN_INCH/INCHES_IN_FOOT) << "\n";
            cout << "  Double:     " << "centimeters=" << setw(10) << value
                << "inches=" << setw(10) <<value/CENTIMETERS_IN_INCH << "feet=" << value/CENTIMETERS_IN_INCH/INCHES_IN_FOOT << "\n\n";
            continue;
        }

        //Case i: calculate centimeters and feet
        else if (unit == 'I' || unit == 'i')
        {
            cout << "Distance in inches(whole number)? ";
            
            //Get user input and validate input
            value = check_validity();

            //Convert and output
            cout << "\n  Integer:    " << "centimeters=" << setw(10) <<static_cast<int>(value * CENTIMETERS_IN_INCH) << "inches="
                << setw(10) << value << "feet=" << value/INCHES_IN_FOOT << "\n";
            cout << "  Double:     " << "centimeters=" << setw(10) <<value * CENTIMETERS_IN_INCH
                << "inches=" << setw(10) << value << "feet=" << static_cast<double>(value)/INCHES_IN_FOOT << "\n\n";
            continue;
        }

        //Case f: calculate centimeters and inches
        else if (unit == 'F' || unit == 'f')
        {
            cout << "Distance in feet(whole number)? ";

            //Get user input and validate input
            value = check_validity();

            //Convert and output
            cout << "\n  Integer:    " << "centimeters=" << setw(10) <<static_cast<int>(value * INCHES_IN_FOOT * CENTIMETERS_IN_INCH) << "inches="
                << setw(10) << value * INCHES_IN_FOOT << "feet=" << value << "\n";
            cout << "  Double:     " << "centimeters=" << setw(10) << value * INCHES_IN_FOOT * CENTIMETERS_IN_INCH
                << "inches=" << setw(10) <<static_cast<double>(value) * INCHES_IN_FOOT << "feet=" << value << "\n\n";
            continue;
        }

        //Case q: quit
        else if (unit == 'Q' || unit == 'q')
        {
            cout << "Good-bye!\n";
            return 0;
        }

        else
        {
            cout << "\n  Invalid option.\n\n";
            fflush(stdin);
            continue;
        }
    }
}

int check_validity()
{
    int value {};
    while (!(cin >> value) || value < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input; enter a non-negative whole number: ";
    }
    return value;
}


/*
Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : c
Distance in centimeters(whole number)? 1

  Integer:    centimeters=1   inches=0     feet=0
  Double:     centimeters=1   inches=0.393701     feet=0.0328084

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : c
Distance in centimeters(whole number)? 100

  Integer:    centimeters=100   inches=39     feet=3
  Double:     centimeters=100   inches=39.3701     feet=3.28084

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : i
Distance in inches(whole number)? 1

  Integer:    centimeters=2   inches=1     feet=0
  Double:     centimeters=2.54   inches=1     feet=0.0833333

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : i
Distance in inches(whole number)? 100

  Integer:    centimeters=254   inches=100     feet=8
  Double:     centimeters=254   inches=100     feet=8.33333

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : r

  Invalid option.

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : f
Distance in feet(whole number)? 1

  Integer:    centimeters=30   inches=12     feet=1
  Double:     centimeters=30.48   inches=12     feet=1

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : f
Distance in feet(whole number)? 100

  Integer:    centimeters=3048   inches=1200     feet=100
  Double:     centimeters=3048   inches=1200     feet=100

Welcome! This program will allow you to convert distances!
What is your starting unit? c)entimeter, i)nch, f)eet, or q)uit : q
Good-bye!

--------------------------------
Process exited after 14.93 seconds with return value 0
*/
