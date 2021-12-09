/*
  Author:         Jonathan Han
  Assignment:     Lab 14, last lab for the semester
  Course/Section: COSC 1337 Section S (change S to your section number)
  Due Date:       See syllabus or blackboard
  Instructor:     Thayer
  Purpose: Practice recursion by implementing looping functions as recursive functions

  For each looping function, provide the code for the equivalent recursive function.
  See Blackboard, Lab 14 for complete instructions.
  
  IMPORTANT: Your recursive functions should NOT use any static local variables
  or global variables! The "state" of the function must be completely self-contained.
  A recursive functions may be called simultaneously by several programs at the same
  time. This occurs when a recursive function is in a library, such as qsort().
  If calls are not independent, the recursive function is limited to a single process.
  
  Use care that your recursive functions call THEMSELVES - not some OTHER function.
  
  Search on "modify" to find places to insert your code or modify existing code.
*/

#include <iostream>
#include <iomanip>
#include <algorithm> // for min, max
using namespace std;

void show_1_to_n_loop(int n) { // looping, PROVIDED, DO NOT CHANGE
    for (int i=1; i<=n; ++i) cout<<i<<" ";
}

//Prints 1 to n. Does all the printing at the end
void show_1_to_n_recurse(int n) { // recursive
    // Constraints: No loops allowed; no static local or global variables.
    if (n == 1) {
        cout << n << " ";
    } else if (n < 1) { //Handles invalid cases
        return;
    } else {
        show_1_to_n_loop(n - 1);
        cout << n << " ";
    }
}

void show_n_to_1_loop(int n) { // looping, PROVIDED, DO NOT CHANGE
    for (int i=n; i>=1; --i) cout<<i<<" ";
}

//Prints n to 1. Does all the printing as the function continues
void show_n_to_1_recurse(int n) { // recursive
    // Constraints: No loops allowed; no static local or global variables.
    if (n == 1) {
        cout << n;
    } else if (n < 1) { //Handles invalid cases
        return;
    } else {
        cout << n << " ";
        show_n_to_1_recurse(n - 1);
    }
}

string reverse_loop(string forward) { // looping, PROVIDED, DO NOT CHANGE
    string backwards;
    int size=forward.size();
    for (int i=0; i<size; ++i) {
        backwards+=forward[size-1-i];
    }
    return backwards;
}

//Flips a string backwards
// Does all the string concatenation work at the end
string reverse_recurse(string forward) { // recursive
    // Constraints: No loops allowed; no static local or global variables.
    if (forward.size() == 1) { //Only the first character is left
        return forward;
    } else { //Multiple characters are left
        return reverse_recurse(forward.substr(1)) + forward[0];
    }
}

int add2_fx(int a, int b) { // functional (for illustration only), PROVIDED, DO NOT CHANGE
    return a+b;
}

int add2_loop(int a, int b) { // looping, PROVIDED, DO NOT CHANGE
    int sum=a;
    if (b>0)
        for (int i=0; i<b; ++i) ++sum;
    else // b<=0
        for (int i=b; i<0; ++i) --sum;
    return sum;
}

//There are 2 major cases, when b is positive and when b is negative
//Change a and return a at the end
//Based on the fact that 7 + 3 = 8 + 2 = 9 + 1 = 10 + 0
int add2_recurse(int a, int b) { // recursive
    // Rule: Do NOT use the *, /, +, =, *=, /=, +=, -=, ^, &, <<, >> operators.
    // DO NOT USE bitwise operators like: (a & b) << 1; These are not part of the course.
    // You MAY use: ++ and/or -- (as done in add2_loop)
    // Constraints: No loops allowed; no static local or global variables.
    // Your new code goes here; modify...
    if (b > 0) { //b is positive
        return add2_recurse(++a, --b);
    } else if (b < 0) { //b is negative
        return add2_recurse(--a, ++b);
    } else { //b is zero
        return a;
    }
}

int mult2_fx(int a, int b) { // functional (for illustration only), PROVIDED, DO NOT CHANGE
    return a*b;
}

int mult2_loop(int a, int b) { // looping, PROVIDED, DO NOT CHANGE
    int product=0;
    if (b>0)
        for (int i=0; i<b; ++i) product+=a;
    else // b<=0
        for (int i=b; i<0; ++i) product-=a;
    return product;
}

//There are 2 major cases, when b is positive and when b is negative
//The base case is when b reaches zero
//Based on the fact that 7 * 3 = 7 + (7 * 2) = 7 + 7 + (7 * 1)
int mult2_recurse(int a, int b) { // recursive
    // Rule: you may NOT use the *, *=, / or /= operators.
    // You MAY use: +, -, +=, -= operators (as done in mult2_loop)
    // Constraints: No loops allowed; no static local or global variables.
    // Your new code goes here; modify...
    if (b > 0) { //If b is positive
        return a + mult2_recurse(a, b - 1);
    } else if (b < 0) { //If b isn't positive
        return mult2_recurse(a, b + 1) - a;
    } else { //b is zero
        return 0;
    }
}

int search_loop(int array[], int size, int target) { // looping, PROVIDED, DO NOT CHANGE
    for (int i=0; i<size; ++i)
        if (array[i]==target) {return i;}
    return -1;
}

//Linear search starting from the back
int search_recurse(int array[], int size, int target) { // recursive
    // Constraints: No loops allowed; no static local or global variables.
    // Your new code goes here; modify...
    if (array[size] == target) { //target is found
        return size;
    } else if (size == 0) { //target is not found
        return -1;
    } else { //Search the rest of the array
        return search_recurse(array, size - 1, target);
    }
}

enum control_flow_t {functional, looping, recursive};
void show_test(int n, string s, control_flow_t control_flow) {
    // utility function to format test output
    // n: test number; s: "description"; control_flow: functional, looping or recursive
    static const string fx="functional", sl="looping", sr="recursive";
    int max_len=max(fx.size(), max(sl.size(), sr.size()));
    string msg;
    switch (control_flow) {
        case functional: msg=fx;     break;
        case looping:    msg=sl;     break;
        case recursive:  msg=sr;     break;
        default:         msg="??";   break;
    }
    char iorr=msg[0];
    msg=" ("+msg+"): ";
    cout<<"\n"<<n<<iorr<<") "<<s<<setw(max_len+5)<<left<<msg;
}

void infinite_recursion() {
    // try at your own risk! Error message can be interesting.
    infinite_recursion();
}

// This code may be helpful when developing your recursive functions.
void recurse(int times_to_call) {
    // a generalized recursion outline; has 5 locations to do work...
    cout << "recurse head... " << "("<<times_to_call<<") " <<endl; // ALWAYS
    if (times_to_call>1) { // decision to recursive call
        cout << "recurse before call... " << "("<<times_to_call<<") " <<endl;
        recurse(times_to_call-1); // work (problem simplification) can be done inside the parameter list!
        cout << "recurse after call... " << "("<<times_to_call<<") " <<endl;
    } else {
        cout << "recurse else option... " << "("<<times_to_call<<") " <<endl;
    }
    cout << "recurse ...tail " << "("<<times_to_call<<") " <<endl; // ALWAYS
}

int main () {
    const string FIRSTNAME{"Firstname"}; // modify / change this to your first name
    const string LASTNAME{"Lastname"};   // modify / change this to your last name

    // ----- DO NOT CHANGE ANY CODE BELOW in main(). CODE BELOW CALLS FUNCTIONS ABOVE FOR TESTING -----

    cout<<"start...\n";

    show_test(1, "show_1_to_n", looping);    show_1_to_n_loop(15);
    show_test(1, "show_1_to_n", looping);    show_1_to_n_loop(-9);    // handle unexpected values
    show_test(1, "show_1_to_n", recursive);  show_1_to_n_recurse(15);
    show_test(1, "show_1_to_n", recursive);  show_1_to_n_recurse(-9); // avoid runaway recursion
    cout<<endl;

    show_test(2, "show_n_to_1", looping);    show_n_to_1_loop(11);
    show_test(2, "show_n_to_1", looping);    show_n_to_1_loop(-5);    // handle unexpected values
    show_test(2, "show_n_to_1", recursive);  show_n_to_1_recurse(11);
    show_test(2, "show_n_to_1", recursive);  show_n_to_1_recurse(-5); // avoid runaway recursion
    cout<<endl;

    show_test(3, "reverse", looping);    cout<<reverse_loop("dad & mom & bob & sis live stressed");
    show_test(3, "reverse", looping);    cout<<reverse_loop(FIRSTNAME);
    show_test(3, "reverse", looping);    cout<<reverse_loop(LASTNAME);
    show_test(3, "reverse", recursive);  cout<<reverse_recurse("mom & dad & bob & sis live stressed");
    show_test(3, "reverse", recursive);  cout<<reverse_recurse(FIRSTNAME);
    show_test(3, "reverse", recursive);  cout<<reverse_recurse(LASTNAME);
    cout<<endl;

    show_test(4, "add2", functional);
    cout<<add2_fx( 4,  5); cout<<" ";  // correct:   9
    cout<<add2_fx(-5, 15); cout<<" ";  // correct:  10
    cout<<add2_fx(20, -9); cout<<" ";  // correct:  11
    cout<<add2_fx(-7, -5); cout<<" ";  // correct: -12
    show_test(4, "add2", looping);
    cout<<add2_loop( 4,  5); cout<<" ";  // correct:   9
    cout<<add2_loop(-5, 15); cout<<" ";  // correct:  10
    cout<<add2_loop(20, -9); cout<<" ";  // correct:  11
    cout<<add2_loop(-7, -5); cout<<" ";  // correct: -12
    show_test(4, "add2", recursive);
    cout<<add2_recurse( 4,  5); cout<<" ";  // correct:   9
    cout<<add2_recurse(-5, 15); cout<<" ";  // correct:  10
    cout<<add2_recurse(20, -9); cout<<" ";  // correct:  11
    cout<<add2_recurse(-7, -5); cout<<" ";  // correct: -12
    cout<<endl;

    show_test(5, "mult2", functional);
    cout<<mult2_fx( 50,   2); cout<<" ";  // correct:  100
    cout<<mult2_fx( 5,  -40); cout<<" ";  // correct: -200
    cout<<mult2_fx(-100,  3); cout<<" ";  // correct: -300
    cout<<mult2_fx(-4, -100); cout<<" ";  // correct:  400
    show_test(5, "mult2", looping);
    cout<<mult2_loop( 50,   2); cout<<" ";  // correct:  100
    cout<<mult2_loop( 5,  -40); cout<<" ";  // correct: -200
    cout<<mult2_loop(-100,  3); cout<<" ";  // correct: -300
    cout<<mult2_loop(-4, -100); cout<<" ";  // correct:  400
    show_test(5, "mult2", recursive);
    cout<<mult2_recurse( 50,   2); cout<<" ";  // correct:  100
    cout<<mult2_recurse( 5,  -40); cout<<" ";  // correct: -200
    cout<<mult2_recurse(-100,  3); cout<<" ";  // correct: -300
    cout<<mult2_recurse(-4, -100); cout<<" ";  // correct:  400
    cout<<endl;

    int primes[] {211, 307, 401, 503, 601, 701, 809, 907, 1009, 1103}; // some numbers to search for
    int size_primes=sizeof(primes)/sizeof(primes[0]);  // get #elements in array

    show_test(6, "search", looping);
    cout<<search_loop(primes, size_primes, 211)<<", ";
    cout<<search_loop(primes, size_primes, 401)<<", ";
    cout<<search_loop(primes, size_primes, 907)<<", ";
    cout<<search_loop(primes, size_primes, 1103);
    show_test(6, "search", recursive);
    cout<<search_recurse(primes, size_primes, 211)<<", ";
    cout<<search_recurse(primes, size_primes, 401)<<", ";
    cout<<search_recurse(primes, size_primes, 907)<<", ";
    cout<<search_recurse(primes, size_primes, 1103)<<endl;

    // infinite_recursion();  // uncomment to experience infinite recursion (crash, error message)

    cout<<"\n...end\n";

    return 0;
} // end of main

// When complete, there will be test output for each of the 6 steps in pairs:
// looping and recursive. Your output should match.
/*
start...

1l) show_1_to_n (looping):    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
1l) show_1_to_n (looping):
1r) show_1_to_n (recursive):  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
1r) show_1_to_n (recursive):

2l) show_n_to_1 (looping):    11 10 9 8 7 6 5 4 3 2 1
2l) show_n_to_1 (looping):
2r) show_n_to_1 (recursive):  11 10 9 8 7 6 5 4 3 2 1
2r) show_n_to_1 (recursive):

3l) reverse (looping):    desserts evil sis & bob & mom & dad
3l) reverse (looping):    emantsriF
3l) reverse (looping):    emantsaL
3r) reverse (recursive):  desserts evil sis & bob & dad & mom
3r) reverse (recursive):  emantsriF
3r) reverse (recursive):  emantsaL

4f) add2 (functional): 9 10 11 -12
4l) add2 (looping):    9 10 11 -12
4r) add2 (recursive):  9 10 11 -12

5f) mult2 (functional): 100 -200 -300 400
5l) mult2 (looping):    100 -200 -300 400
5r) mult2 (recursive):  100 -200 -300 400

6l) search (looping):    0, 2, 7, 9
6r) search (recursive):  0, 2, 7, 9

...end

Process finished with exit code 0

*/
