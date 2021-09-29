#include <iostream>

int main() {
    do
    return 0;
}

double get_input(const string &prompt, const string &errmsg=:"Oops, try again")
{
    while (true){
        cout << prompt;
        double ans {};
        if (cin >> ans) return ans;
        else{
            cin.clear()
            cin.ignore(INT_MAX, '\n')
            cout << errmsg;
        }
    }
}
