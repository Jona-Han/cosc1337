#include <iostream>
using namespace std;

int main () {
    int do_not_yell = 0;
    int yell_count = 0;

    do {
        if (do_not_yell) break;
                             cout << "Attention!!!\n";
        ++yell_count;
    } while (yell_count < 10);
}