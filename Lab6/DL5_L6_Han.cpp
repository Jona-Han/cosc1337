/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 6: Calculates and displays the distance between letters, numbers, or points. Uses functions.
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//Prototypes
char input(const string &prompt_text = "Enter character", const string &error_message = "Sorry, try again.");
double input(double min_value, double max_value, string error_message, const string &prompt_text = "Enter number");
void input(double &x_value, double &y_value, const string &prompt_text = "Enter point");
int dist(char a, char b);
double dist(double d1, double d2);
double dist(double x1, double y1, double x2, double y2);
void display(char ch1, char ch2, const string &msg = "Distance between letters");
void display(double d1, double d2, const string &msg = "Units between");
void display(double x1, double y1, double x2, double y2, const string &msg = "Straight line distance between points");
void change_one_or_two (int &one_or_two);

int main() {
    enum Options {letter = 'l', number = 'n', point = 'p', quit = 'q'};
    cout << "Display the distance between two items: letters, numbers, or points.\n\n";

    while (true) { //Main menu
        cout << "Options: l)etter; n)umber; p)oint; q)uit: ";

        //Get user selected option and convert to Options type
        char user_inputted_option;
        cin >> user_inputted_option;
        Options converted_user_option {static_cast<Options>(tolower(user_inputted_option))};

        switch (converted_user_option) {
            case letter: {
                char char_1 {input()}; //Get inputs
                char char_2 {input()};
                display(char_1, char_2); //Print distance
                break;
            }
            case number: {
                //Get inputs
                double double_1 {input(-100, 100, "Sorry, out of range. Try again.")};
                double double_2 {input(-200, 200, "Sorry, out of range. Try again.")};
                display(double_1, double_2); //Print distance
                break;
            }
            case point: {
                //Get inputs
                double x1, y1;
                input(x1, y1);
                double x2, y2;
                input(x2, y2);
                display(x1, y1, x2, y2); //Print distance
                break;
            }
            case quit: {
                cout << "Good-bye!\n";
                exit(EXIT_SUCCESS);
            }
            default: {
                cout << "Invalid option.\n";
                break;
            }
        }
        cout << endl;
    }
}

//Gets and returns a valid character input
char input(const string &prompt_text, const string &error_message) {
    static int one_or_two {1}; //Keeps track of whether the function has been called once or twice
    cout << string(2, ' ') << prompt_text << ' ' << one_or_two << " (a-z): ";

    //Input validation loop
    char user_input;
    while (!(cin >> user_input and isalpha(user_input))) {
        cout << string(4, ' ') << error_message << endl;
        cout << string(2, ' ') << prompt_text << ' ' << one_or_two << " (a-z): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    change_one_or_two(one_or_two); //Changes one_or_two for the next call
    return user_input;
}

//Gets and returns valid number input
double input(double min_value, double max_value, string error_message, const string &prompt_text) {
    static int one_or_two {1};
    cout << string(2, ' ') << prompt_text << ' ' << one_or_two << '(' << min_value << ',' << max_value << "): ";

    //Input validation loop
    double user_input;
    while (!(cin >> user_input and user_input <= max_value and user_input >= min_value)) {
        cout << string(4, ' ') << error_message << endl << string(2, ' ') << prompt_text << ' '
             << one_or_two << '(' << min_value << ',' << max_value << "): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    change_one_or_two(one_or_two);
    return user_input;
}

//Gets and x and y coordinate and assigns the input
void input(double &x_value, double &y_value, const string &prompt_text){
    static int one_or_two {1};
    char x_or_y {'x'}; //Keeps track of whether the x or y coordinate is being obtained

    while (true) {
        cout << string(2, ' ') << prompt_text << ' ' << one_or_two << " (" << x_or_y << "): ";

        //Input validation loop
        double user_input;
        while (!(cin >> user_input and user_input <= 100 and user_input >= -100)) {
            cout << string(4, ' ') << "Invalid. Enter a number between -100 and 100." << endl << string(2, ' ')
                 << prompt_text << ' ' << one_or_two << " (" << x_or_y << "): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        //Checks whether x or y is being obtained and initializes the corresponding variable
        if (x_or_y == 'x') {
            x_value = user_input;
            x_or_y = 'y';
            continue;
        }
        y_value = user_input;
        break;
    }
    change_one_or_two(one_or_two);
}

int dist(char a, char b) { //Calculates distance between letters
    return abs(tolower(a) - tolower(b));
}

double dist(double d1, double d2) { //Calculates distance between numbers
    return abs(d1 - d2);
}

double dist(double x1, double y1, double x2, double y2) { //Calculates distance between points
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void display(char ch1, char ch2, const string &msg) { //Displays character distance calculation
    static int call_count {1}; //Keeps track of how many times the function has been called
    cout << "  (#" << call_count << ") " << msg << ' ' << ch1 << " & " << ch2 << " = " << dist(ch1, ch2) << endl;
    call_count += 1;
}

void display(double d1, double d2, const string &msg) { //Displays number distance calculation
    static int call_count {1};
    cout << "  (#" << call_count << ") " << msg << ' ' << d1 << " and " << d2 << " = " << dist(d1, d2) << endl;
    call_count += 1;
}

void display(double x1, double y1, double x2, double y2, const string &msg) { //Displays point distance calculation
    static int call_count {1};
    cout << "  (#" << call_count << ") " << msg << " (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")"
         << " = " << dist(x1, y1, x2, y2) << endl;
    call_count += 1;
}

void change_one_or_two(int &one_or_two) { //Changes variable keeping track of which function call
    if (one_or_two == 1)
        one_or_two = 2;
    else
        one_or_two = 1;
}

/*
TEST OUTPUT:
./DL5_L6_Han
Display the distance between two items: letters, numbers, or points.

Options: l)etter; n)umber; p)oint; q)uit: l
  Enter character 1 (a-z): b
  Enter character 2 (a-z): f
  (#1) Distance between letters b & f = 4

Options: l)etter; n)umber; p)oint; q)uit: n
  Enter number 1(-100,100): -5.5
  Enter number 2(-200,200): 20.5
  (#1) Units between -5.5 and 20.5 = 26

Options: l)etter; n)umber; p)oint; q)uit: p
  Enter point 1 (x): 0
  Enter point 1 (y): 3
  Enter point 2 (x): 4
  Enter point 2 (y): 0
  (#1) Straight line distance between points (0, 3) and (4, 0) = 5

Options: l)etter; n)umber; p)oint; q)uit: l
  Enter character 1 (a-z): 8
    Sorry, try again.
  Enter character 1 (a-z): A
  Enter character 2 (a-z): z
  (#2) Distance between letters A & z = 25

Options: l)etter; n)umber; p)oint; q)uit: n
  Enter number 1(-100,100): -123.456
    Sorry, out of range. Try again.
  Enter number 1(-100,100): -10
  Enter number 2(-200,200): -201
    Sorry, out of range. Try again.
  Enter number 2(-200,200): 50
  (#2) Units between -10 and 50 = 60

Options: l)etter; n)umber; p)oint; q)uit: p
  Enter point 1 (x): 0
  Enter point 1 (y): 0
  Enter point 2 (x): 1
  Enter point 2 (y): 1
  (#2) Straight line distance between points (0, 0) and (1, 1) = 1.41421

Options: l)etter; n)umber; p)oint; q)uit: u
Invalid option.

Options: l)etter; n)umber; p)oint; q)uit: q
Good-bye!
 */