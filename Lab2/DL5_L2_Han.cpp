/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 2: Create diamonds of various sizes determined by the user
 */

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    while (true)
    {
        cout << "Hello, this application will allow you to create a diamond.\n";
        cout << "Please enter the size of your diamond or 0 to quit:  ";
        int number_of_lines {};
        while (!(cin >> number_of_lines))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a whole number or 0 to quit:  ";
        }

        if (number_of_lines <= 0)
        {
            cout << "Goodbye!" << endl;
            return 0;
        }

        //Build top half of diamond
        cout << endl;
        for (int i = 1; i <= number_of_lines; i += 2)
        {
            cout << string((number_of_lines - i) / 2, ' ') << string(i, '*') << endl;
        }

        //Build bottom half of diamond
        for (int i = 2 * (number_of_lines / 2) - 1; i >= 1; i -= 2)
        {
            cout << string((number_of_lines - i) / 2, ' ') << string(i, '*') << endl;
        }
        cout << endl;
    }
}

//The following loop only works for odd diamonds
/*
        int mid_plus_one = number_of_lines / 2 + 1;
        //Draw odd diamond
        for (int i = 1; i <= number_of_lines; i++)
        {
            for (int j = 0; j < abs(mid_plus_one - i); j++)
            {
                cout << ' ';
            }
            for (int j = 0; j < (number_of_lines - 2 * abs(mid_plus_one - i)); j++)
            {
                cout << '*';
            }
            cout << endl;
        }
        cout << endl;
*/