/*
  Author:
  Section:
  Course: COSC1337
  Topic: lab 11, calendar helper, startup code
  Note: This code provides a test bed for class Day. Testing class Day should be easy and complete.
  You do not have the startup code exactly as is, but it should provide easy options to test class Day.
  
*/

#include <iostream>
#include <ctype.h>
#include <iomanip>
#include <string>
using namespace std;

template<typename T> // useful for getting user's keyboard input without crash or hang
T kbd_input(const string &prompt="Enter: ", const string &errmsg="  Oops! Try again.\n\n") {
    while (true) {
        cout << prompt; T ans{};
        if (cin>>ans) return ans;
        else {
            cin.clear(); cin.ignore(INT_MAX, '\n'); cout<<errmsg;
        }
    }
}


class Day {
private:
    int day_of_year; // limit day_of_year to positive numbers

public:
    // month:
    static const int daysInMonth[12];
    static const int daysInMonth_accum[12];
    static const string monthsOfYear[12];
    enum month_t {jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

    // week
    static const string daysOfWeek[7];  // Initialized to: {"sunday", "monday", "tuesday", ... "saturday"};
    enum weekday_t {sun, mon, tue, wed, thr, fri, sat};// may be useful

    // day
    static const int BASE_YEAR=2021;
    static const month_t BASE_MONTH=jan;
    static const weekday_t BASE_WEEKDAY=fri; // January 1, 2021 was a Friday
    static const int BASE_DAY=1;

    // Much to do: implement 3 constructors, ++day, day++, --day, day--; "show", "print", "display", << as needed
    Day() {
        day_of_year = 1;
    }

    Day(int day_of_year) {
        if (day_of_year >= 1) {
            this->day_of_year = day_of_year;
        } else {
            this->day_of_year = 1;
            cout << "Invalid Day. Day must be positive. Using a default value of 1.\n";
        }
    }

    Day(string month, int day) {
        month_t providedMonth;
        for (int monthIndex = 0; monthIndex < 12; monthIndex++) {
            if (month == monthsOfYear[monthIndex]) {
                providedMonth = static_cast<month_t>(monthIndex);
            } else if (monthIndex == 11) {
                cout << "Invalid month provided. Did you check the spelling? "
                        "The month must be 3 characters (jan, feb, mar, ...)\n";
                cout << "Using a default month of jan\n";
                providedMonth = jan;
            }
        }

        if (day > daysInMonth[providedMonth] || day < 1) {
            cout << "Invalid day value for month. For month " << providedMonth << " day must be between 1 and "
                 << daysInMonth[providedMonth] << ".\n" << "Using a default value of 1.\n";
            day = 1;
        }

        day_of_year = daysInMonth_accum[providedMonth] + day;
    }

    Day operator++() {
        day_of_year++;
        return *this;
    }

    Day operator--() {
        if (day_of_year > 1) {
            day_of_year--;
        }
        return *this;
    }

    Day operator++(int) {
        Day temp = *this;
        day_of_year++;
        return temp;
    }

    Day operator--(int) {
        Day temp = *this;
        if (day_of_year > 1) {
            day_of_year--;
        }
        return temp;
    }

    inline const int getDay() {
        return day_of_year;
    }

    // Members can be here (inline) or after.
};

// Use these as needed
 const int Day::daysInMonth[12] = {31, 28, 31, 30,  31,  30,  31,  31,  30,  31,  30,  31};
 const int Day::daysInMonth_accum[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
 const string Day::monthsOfYear[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
 const string Day::daysOfWeek[7] = {"sun", "mon", "tue", "wed", "thr", "fri", "sat"};

int main() {
    const int BASE_YEAR = 2021;
    const int FIRST_DAY_OF_2021 = 4;
    cout <<"Welcome to Jonathan's calendar helper!\n";
    Day day; // this is updated in the set day options, and is the 1st day displayed in the Display options.
    for (bool running=true; running; ) {
        cout<<"\nOptions: Display d)ay w)eek m)onth; s)et-day t)esting q)uit: ";
        string option; char option_letter; cin>>option; option_letter=tolower(option[0]);
        switch (option_letter) {
            case 'd': {
                string dayOfWeek = Day::daysOfWeek[day.getDay() % 7 + FIRST_DAY_OF_2021];
                cout <<"Day# = [" << day.getDay() << "] " << dayOfWeek << "\n";
                break;
            }

            case 'w': {
                cout<<"w option - show a week of days starting at current day, TO BE IMPLEMENTED\n";
                break;
            }

            case 'm': {
                cout<<"m option - show a month of days starting at current day, TO BE IMPLEMENTED\n";
                break;
            }

            case 's': // set day, test constructors: Day(), Day(int) constructor
            {
                char option = tolower(kbd_input<char>("  set day d)efault m)month,day n)umber v)ary: "));
                if (option=='q') break;

                switch(option) {
                    case 'd': { // d=default: use default for an instance of class Day
                        cout<<"    set day d option - TO BE IMPLEMENTED\n";
                        break;
                    }

                    case 'm': {  // m=month day: ask user for month and day of month, use user's input to construct a Day
                        cout<<"    set day m option - TO BE IMPLEMENTED\n";
                        break;
                    }

                    case 'n': { // n=number: ask user for number 1..365..etc., use user's input to construct a Day
                        cout<<"    set day n option - TO BE IMPLEMENTED\n";
                        break;
                    }

                    case 'v': { // v=vary: ask user for amount (can negative, 0, positive), vary current day by that amount
                        cout<<"    set day v option - TO BE IMPLEMENTED\n";
                        break;
                    }

                    default: // not a valid option
                        cout<<"    set day Invalid option.\n"; break;// continue;
                }
                // cout<<"  day#=["<<day<<"] "<<day.to_string()<<endl; // generic output. Could be helpful.
                break;
            } // case 's' for set day

            case 't': {
                cout<<"t option - test increment ++, decrement operators --, TO BE IMPLEMENTED\n";
                break;
            }

            case 'q':
                running=false;
                break;

            default:
                cout<<"  Invalid option, try again. q to quit.\n";
                break;
        }
    }
    cout<<"\nThanks for using ??????s calendar helper! Good-bye!";
}

/*

*/
