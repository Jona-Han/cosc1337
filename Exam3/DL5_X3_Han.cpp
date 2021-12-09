/*
  COSC 1337 Exam 3 Lab portion
  Name: Jonathan Han
  Filename: DL5_X3_Han.cpp
    before submitting, change the file name
      from: DLS_X3_Lastname.cpp
      to:   <your course designator>_X3_<your last name>.cpp
      where DLS is Distance Learning Section (example: DL2, DL5)
      
    NOTE: In devcpp, use compiler options (Tools -> Compiler Options) put: -std=c++14
    otherwise, you may get this error:
    [Warning] extended initializer lists only available with -std=c++11 or -std=gnu++11 
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

// Part 1A, 1B, 1C: create function box, box(wide, tall, symbol)
string box(const int wide = -1, const int tall = -1, const char symbol = '*') {
    string finalString{};
    static int perimeterAccumulator;

    if (wide < 0) {
        return to_string(perimeterAccumulator);
    } else if (tall < 0) {
        for (int rowNumber = 0; rowNumber < wide; rowNumber++) {
            finalString += string(wide, symbol);
            finalString += "\n";
        }
        perimeterAccumulator += 4 * wide;
    } else {
        for (int rowNumber = 0; rowNumber < tall; rowNumber++) {
            finalString += string(wide, symbol);
            finalString += "\n";
        }
        perimeterAccumulator += 2 * wide + 2 * tall;
    }
    return finalString;
}

void part1() {
    // ------------------ section below is provided for testing, it is called from main
    cout<<"part 1:\n";
    // Testing for part 1D, 2 points, code provided
    cout<<"part 1D: box testing 2 points:\n";
    cout << box(9, 3, '=') << endl << endl;
    cout << box(5, 2) << endl << endl;
    cout << box(3) << endl << endl;
    cout << box() << endl << endl;
    cout<<endl;
    // --------------section above code is provided for testing, do not change

    cout<<"part 1D: more box testing 3 points:\n";
    // Display 3 small boxes. Use digits from your ACCeID for wide and tall. For digit 0, use 10.
    // Use the first letter of your first name for the symbol.
    // Example 1: ACCeID "f1234567", boxes are: box(1,  2, 'f'); box(3, 4, 'f'); box(5,  6, 'f');
    // Example 2: ACCeID "s3052042", boxes are: box(3, 10, 's'); box(5, 2, 's'); box(10, 4, 's');
    cout << box(2, 1, 'j') << endl << box(9, 9, 'j') << endl << box(2, 2, 'j') << endl;
    cout << endl;
}

// Put your code for part 2A, 2B, 2C here, class Rect
class Rect {
private:
    int wide;
    int tall;
    char symbol;

public:
    static int numberOfInstances;   //Keeps track of number of Rect instances

    //Constructor. Uses * as character if none provided
    Rect(const int wide, const int tall, const char symbol = '*') {
        this->wide = wide;
        this->tall = tall;
        this->symbol = symbol;
        numberOfInstances++;
    }

    //Constructor. If no tall is provided, uses wide as tall
    Rect(const int wide) {
        this->wide = wide;
        tall = wide;
        symbol = '*';
        numberOfInstances++;
    }

    //Default constructor. Uses 0 for wide and tall. Uses a space as symbol
    Rect() {
        wide = 0;
        tall = 0;
        symbol = ' ';
        numberOfInstances++;
    }

    //Returns a string version of a Rect object
    string toString() {return box(wide, tall, symbol);}

    //Overloaded pre-increment operator. Adds 1 to wide and tall
    Rect operator++ () {
        wide++;
        tall++;
    }

    //Overloaded addition operator. Adds the wide and tall of 2 rectangles to form a new third rectangle.
    //Uses the larger area of each rectangle as the new rectangle's symbol
    Rect operator+(Rect r2) {
        int width = this->wide + r2.wide;
        int height = this->tall + r2.tall;
        char symb;
        if (this->wide * this->tall > r2.wide * r2.tall) {
            symb = this->symbol;
        } else {
            symb = r2.symbol;
        }
        return Rect(width, height, symb);
    }
};
int Rect::numberOfInstances = 0; //Set static class variable to 0


void part2() {
    cout<<"part 2:\n";
    // Put your code for part 2 here, it will be called from main:
    cout<<"part 2D: Rect testing 3 points:\n";

     Rect rect1(1, 3, '=');
     Rect rect2(5, 4);
     Rect rect3(3);
     Rect rect4;
     Rect rect5(-5, -6);

    // Put 5 instances of Rect into a vector; in a loop, show each Rect in the vector, followed by blank line
    vector<Rect> vectorOfRects;
    vectorOfRects.push_back(rect1);
    vectorOfRects.push_back(rect2);
    vectorOfRects.push_back(rect3);
    vectorOfRects.push_back(rect4);
    vectorOfRects.push_back(rect5);

    for (auto rectangle : vectorOfRects) {
        cout << rectangle.toString();
        cout << endl;
    }

    //Display the number of Rect instances. Should be 5.
    cout << "\nNumber of Rect instances: " << Rect::numberOfInstances << endl;
    cout << endl;
}


void part3() {
    cout<<"part 3:\n";
    cout<<"part 3: testing pointers, dynamic memory using Rect\n";
    // Rect(1234, 567, 'a'); // P3A, constructing Rect example, using ACCeID: a1234567

    //Dynamically construct a Rect object and display its address
    Rect *pDynamicRect = new Rect(2199, 222, 'j');
    cout << "Rect is at address: " << pDynamicRect << endl;

    //Dynamically allocate an array of 5000 Rect objects and set each object to default Rect
    Rect *pArrayOf5000Rects = new Rect[5000];
    for (int arrayIndex = 0; arrayIndex < 5000; arrayIndex++) {
        pArrayOf5000Rects[arrayIndex] = Rect();
    }

    //Display the addresses of the first, middle, and last Rect in the array
    cout << "First in Rect array at: " << pArrayOf5000Rects << endl;
    cout << "Middle in Rect array at: " << pArrayOf5000Rects + 2499 << endl;
    cout << "Last in Rect array at: " << pArrayOf5000Rects + 4999 << endl;

    // Deallocate memory allocated above
    delete pDynamicRect;
    pDynamicRect = nullptr;
    delete [] pArrayOf5000Rects;
    pArrayOf5000Rects = nullptr;

    cout<<endl;
};


void part4() {
    // Below is testing code for part 4; it will be called from main. No changes needed.
    cout<<"part 4:\n";
    cout<<"part 4: testing operator++\n";

    Rect r(4,2);
    for (int i{}; i<3; ++i) {
      cout << r.toString() << endl;
      ++r;
    }

    cout<<"part 4: testing operator+\n";
    Rect r1(5, 4, 'L');
    Rect r2(3, 2, 'S');
    Rect r3=r1+r2;
    cout << "Rect r1(5, 4, 'L') + Rect r2(3, 2, 'S') = Rect r3:\n";
    cout << r1.toString() << endl;
    cout << r2.toString() << endl;
    cout << r3.toString() << endl; // uncomment when ready to test; r3 should be: 8 wide * 6 tall using 'L'
    cout << endl;

};

void part5() { // EXTRA CREDIT
    cout<<"part 5: (optional extra credit)\n";
    // ----------------- This section allocates some memory, but never deletes it
    class Horse { // make instances of class Horse, optimized to make allow a list of horses
        string name;     // name of the horse, defaults to ""
        double height{}; // height of the horse, defaults to 0.0
        Horse *next{};   // pointer to the next horse, defaults to nullptr
    public:
        Horse(string name, double height, Horse *next=nullptr) {
            this->name=name; this->height=height; this->next=next;
        }
        Horse *get_next() const {
            return next;
        };
    };

    char *p_buffer = new char[50000];
    int *p_int = new int;
    Horse *p_horses = new Horse("Zella", 50, new Horse("Yankee", 60));
    Horse *p_paddock = new Horse[3]{Horse("Alex", 70), Horse("Buster", 80), Horse("Crippix", 90)};
    //---------------------------------------------------------------------
    // Put your code for part 5 here: Delete any memory left on the heap above to prevent memory leak
    // Hint: there are 5 new, so there must be 5 delete. No need to reset pointers to nullptr.
    // No need to display anything to output, just provide appropriate delete statements.
    delete [] p_buffer;
    delete p_int;
    delete p_horses->get_next();
    delete p_horses;
    delete [] p_paddock;
};

int main() {
    // No new code goes in main. Put all new code where designated in the parts above.
    const int COURSE {1337};
    cout<<"COSC " << std::to_string(COURSE) << " Exam 3 Part 3 Start...\n\n"; // example of std::to_string()
    part1();
    part2();
    part3();
    part4();
    part5();  // EXTRA CREDIT: free up (delete) memory to prevent memory leak
    cout<<"\n...End.\n";
    return 0;
}
/* Put the test output here. Part 6, 5 points.
COSC 1337 Exam 3 Part 3 Start...

part 1:
part 1D: box testing 2 points:
=========
=========
=========


*****
*****


***
***
***


50


part 1D: more box testing 3 points:
jj

jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj
jjjjjjjjj

jj
jj


part 2:
part 2D: Rect testing 3 points:
=
=
=

*****
*****
*****
*****

***
***
***


138

Number of Rect instances: 5

part 3:
part 3: testing pointers, dynamic memory using Rect
Rect is at address: 0x12d6066f0
First in Rect array at: 0x130008000
Middle in Rect array at: 0x13000f524
Last in Rect array at: 0x130016a54

part 4:
part 4: testing operator++
****
****

*****
*****
*****

******
******
******
******

part 4: testing operator+
Rect r1(5, 4, 'L') + Rect r2(3, 2, 'S') = Rect r3:
LLLLL
LLLLL
LLLLL
LLLLL

SSS
SSS

LLLLLLLL
LLLLLLLL
LLLLLLLL
LLLLLLLL
LLLLLLLL
LLLLLLLL


part 5: (optional extra credit)

...End.

Process finished with exit code 0
*/
