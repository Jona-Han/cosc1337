#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//Prototypes
void change_one_or_two (int &one_or_two);
char input(const string &prompt_text = "Enter character", const string &error_message = "Sorry, try again.");
double input(double min_value, double max_value, string error_message, const string &prompt_text = "Enter number");
void input(double &x_value, double &y_value, const string &prompt_text = "Enter point");
int dist(char a, char b);
double dist(double d1, double d2);
double dist(double x1, double y1, double x2, double y2);
void display(char ch1, char ch2, const string &msg = "Distance between letters");
void display(double d1, double d2, const string &msg = "Units between");
void display(double x1, double y1, double x2, double y2, const string &msg = "Straight line distance between points");

int main() {
    enum Options {letter = 'l', number = 'n', point = 'p', quit = 'q'};
    cout << "Display the distance between two items: letters, numbers, or points.\n\n";

    while (true) {
        cout << "Options: l)etter; n)umber; p)oint; q)uit: ";

        char user_inputted_option {};
        Options converted_user_option {};
        cin >> user_inputted_option;
        converted_user_option = static_cast<Options>(tolower(user_inputted_option));

        switch (converted_user_option) {
            case letter: {
                char char_1 {};
                char char_2 {};
                char_1 = input();
                char_2 = input();
                display(char_1, char_2);
                break;
            }
            case number: {
                double double_1 {};
                double double_2 {};
                double_1 = input(-100, 100, "Sorry, out of range. Try again.");
                double_2 = input(-200, 200, "Sorry, out of range. Try again.");
                display(double_1, double_2);
                break;
            }
            case point: {
                double x1 {};
                double y1 {};
                input(x1, y1);

                double x2 {};
                double y2 {};
                input(x2, y2);
                display(x1, y1, x2, y2);
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

char input(const string &prompt_text, const string &error_message) {
    char user_input {};
    static int one_or_two {1};
    cout << string(2, ' ') << prompt_text << ' ' << one_or_two << " (a-z): ";
    while (!(cin >> user_input and isalpha(user_input))) {
        cout << string(4, ' ') << error_message << endl << string(2, ' ') << prompt_text << ' '
             << one_or_two << " (a-z): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    change_one_or_two(one_or_two);
    return user_input;
}

double input(double min_value, double max_value, string error_message, const string &prompt_text) {
    double user_input {};
    static int one_or_two {1};
    cout << string(2, ' ') << prompt_text << ' ' << one_or_two << '(' << min_value << ',' << max_value << "): ";
    while (!(cin >> user_input and user_input <= max_value and user_input >= min_value)) {
        cout << string(4, ' ') << error_message << endl << string(2, ' ') << prompt_text << ' '
             << one_or_two << '(' << min_value << ',' << max_value << "): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    change_one_or_two(one_or_two);
    return user_input;
}

void input(double &x_value, double &y_value, const string &prompt_text){
    double user_input {};
    static int one_or_two {1};
    char x_or_y {'x'};

    while (true) {
        cout << string(2, ' ') << prompt_text << ' ' << one_or_two << " (" << x_or_y << "): ";
        while (!(cin >> user_input and user_input <= 100 and user_input >= -100)) {
            cout << string(4, ' ') << "Invalid. Enter a number between -100 and 100." << endl << string(2, ' ')
                 << prompt_text << ' ' << one_or_two << " (" << x_or_y << "): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
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

int dist(char a, char b) {
    return abs(tolower(a) - tolower(b));
}

double dist(double d1, double d2) {
    return abs(d1 - d2);
}

double dist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void display(char ch1, char ch2, const string &msg) {
    static int call_count {1};
    cout << "  (#" << call_count << ") " << msg << ' ' << ch1 << " & " << ch2 << " = " << dist(ch1, ch2) << endl;
    call_count += 1;
}

void display(double d1, double d2, const string &msg) {
    static int call_count {1};
    cout << "  (#" << call_count << ") " << msg << ' ' << d1 << " and " << d2 << " = " << dist(d1, d2) << endl;
    call_count += 1;
}

void display(double x1, double y1, double x2, double y2, const string &msg) {
    static int call_count {1};
    cout << "  (#" << call_count << ") " << msg << " (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")"
         << " = " << dist(x1, y1, x2, y2) << endl;
    call_count += 1;
}

void change_one_or_two (int &one_or_two) {
    if (one_or_two == 1)
        one_or_two = 2;
    else
        one_or_two = 1;
}

