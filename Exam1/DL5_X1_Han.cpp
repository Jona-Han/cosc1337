/*
  Name: Jonathan han
  COSC 1337
  Exam 1, Programming portion
  When complete: Change course designator in filename from DLS to DL<section number>
                 Change "Lastname" to your lastname.
  Upload file DL(sec#)_X1_Lastname.cpp to BlackBoard.
*/

#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

/* INSTRUCTIONS:
  There are 4 regular steps (40 points) and 2 extra credit steps (4 points).
  Some algorithms and IPOs (Input, Processing, Output) are provided.
  The term: "input" may refer to keyboard input from the user; OR
  "input" may refer to input to a function as a function parameter.
  
  Step 1. (10 points)
  A common task in geometry is to find the area of a shape.
  Example areas: square (side * side); rectangle (height * width);
  circle (pi * radius_squared); triangle (1/2 * base * height)
  
  Write 4 overloaded functions, all called area,
  that return the area of different shapes: (the return is type double)
    area(side)   one parameter, assume shape is a square
    area(radius) one parameter, assume shape is a circle
    area(height, width) two parameters, assume shape is a rectangle
    area(base, height)  two parameters, assume shape is a triangle
  The return type of all area functions is type double
  
  To help the compiler decide WHICH area function to call, use
  different numeric types for the parameters. Choose from: float, double.
  For example, side has to be one numeric type, radius has to be a different numeric type.
  It doesn't matter which types (float or double), but they have to be different.
  
  Similarly, for area of rectangle, the types for height and width must be
  different than the types for triangle base and height. That way, the compiler
  can call the correct function. The parameter types help decide which
  kind of shape is involved.
  
  For the value of pi (3.1415926...) use M_PI. To make this useful constant
  available, put the following two lines in the correct place in the program:
  #define _USE_MATH_DEFINES
  #include <cmath>
  
  After the area functions are complete, test them. (See test code below in main.)
  To get the compiler to call the desired area function, use arguments
  of the correct type. Testing code is provided below in main. Some changes are needed.
  
  (2) points for each area function (4*2=8), (2) points for testing, total (10) points.
*/

double area() { // provided for step 1, step 2 so initial test code compiles; leave this unchanged
  return 123.456;
}

// provide 4 overloaded area() functions for step 1 here:

double area(float side) { //Area of square
    return side * side;
}

double area(double radius) { //Area of circle
    return M_PI * radius * radius;
}

double area(float height, float width) { //Area of rectangle
    return height * width;
}

double area(double base, double height) { //Area of triangle
    return 0.5 * base * height;
}

/*
  Step 2. (10 points)
  Another strategy to compute the area for a particular shape is to
  just tell the function what kind of shape it is, then use the provided
  parameters as expected for that shape. Using default parameters, the
  area for each shape can be computed, provided the type of shape and the
  one or two parameters needed to compute that shape's area.
  
  Create a function: area(type-of-shape, dimension1, dimension2)
  Use type double for the return, dimension1, and dimension2
  Use the table below to write the function body:
  
  type-of-shape  | dimension1  |  dimension2  |  area
  ---------------|-------------|--------------|--------
  Square         |    side     |  not-needed  | size*side
  Rectangle      |   height    |    width     | height*width
  Circle         |   radius    | not-needed   | PI*radius_squared
  Triangle       |    base     |    height    | 1/2 * base * height
  
  To create the type-of-shape, use an enumerated type, enum, for shapes.
  Hint: recall enum direction_t{North, South, East, West}
  Use a switch to switch on the type-of-shape, then provide a case
  for each valid shape. Based on the shape, return the proper area.
  
  
  This adds one more overloaded function, also called area, which
  can be easier to use.
  
  (8) points for area function, (2) points for testing, total (10) points.
*/


// Create the shape type and area function here:

enum Shape {Square, Circle, Rectangle, Triangle};
double area(Shape type_of_shape, double dimension1, double dimension2 = 1) {
    switch (type_of_shape) {
        case Square:
            return dimension1 * dimension1;
        case Circle:
            return M_PI * dimension1 * dimension1;
        case Rectangle:
            return dimension1 * dimension2;
        case Triangle:
            return 0.5 * dimension1 * dimension2;
    }
}



/*
  Step 3. (10 points)
  A common group of statistical values are: minimum, maximum, sum, difference, average.
  For short: min, max, sum, dif, avg.
  For example, numbers 10 and 100 produce: min=10, max=100, sum=110, dif=90, avg=55

  Write a single function, stats, that provides all of these values, based on
  two input parameters, num1 and num2; and five output parameters (the results). (5 points.)
  Provide correct types for each parameter.
  
  Below in main, activate testing code to call this function.
  See testing instructions lower in main.
  
  (5) points for stats function, (5) points for testing, total (10) points.
*/


 void stats(int num1, int num2, int &min, int &max, int &sum, int &dif, int &avg) { // uncomment when ready
     if (num1 > num2) {
         max = num1;
         min = num2;
     }
     else {
         max = num2;
         min = num1;
     }
         sum = num1 + num2;
         dif = abs(num1 - num2);
         avg = (num1 + num2) / 2;
 }


/*
  Step 4. (10 points)

  A common programming task is to get numerical input from the user.
  Write a single function "get_num" that will:
    1) Display a prompt
    2) Get user's input (from keyboard)
    3) Verify that the input is numeric
    4) If the input is NOT numeric, display err_msg1, fix cin, and loop up to 1)
    5) Check if the numeric value is within range, min..max, inclusive
    6) If the input is in range, accept it and return
    7) If the input is not in range, display err_msg2 and loop up to 1)

    Create a new function that performs the steps above. Use the following:
      1) Function name: get_num
      2) Parameter: prompt      (pass by constant reference)
      3) Parameter: err_msg1    (pass by constant reference)
      4) Parameter: err_msg2    (pass by constant reference)
      5) Parameter: min         (pass by value, type double)
      6) Parameter: max         (pass by value, type double)
      7) return: value          (type double)

  (8) points for get_num function, (2) points for testing, total (10) points.
*/

  // step 4 (8 of 10 points) function get_num() goes here ---

template <typename T>
T get_num(T min, T max, const string &prompt, const string &err_msg1,
           const string &err_msg2 = "Not in range, do-over") {
    T user_input;
    while (true) {
        cout << prompt;
        if (!(cin >> user_input)) {
            cout << string(2, ' ') << err_msg1 << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        else if (!(user_input <= max and user_input >= min)) {
            cout << string(2, ' ') << err_msg2 << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        break;
    }
    return user_input;
}

/*
  Step 5. (2 points) EXTRA CREDIT, OPTIONAL
    Turn step 4 function "get_num" above into a function template, so it works
    for any numeric type: char, short, int, float, double, etc. instead of just double.
    Hint: template <typename T>


  Step 6. (2 points) EXTRA CREDIT, OPTIONAL
    Use this: {"One", "more", "line", "of", "code", "and", "I", "am", "outta", "here"}
    as an initializer list in a range-for loop, so each word is displayed in a sentence.
    The words should be seperated by spaces and end with a period:
      One more line of code and I am outta here.
    To implement, put your code in function step6() below, and uncomment step6() at the end of main.
*/

void step6() {
  cout<< "\nstep 6 (EC): Statement of conviction:\n ";
  string words[10] = {"One", "more", "line", "of", "code", "and", "I", "am", "outta", "here"};
  for (int word_index = 0; word_index < 10; word_index++) {
      if (word_index == 9) {
          cout << words[word_index] << ".\n";}
      else {
          cout << words[word_index] << ' ';}
  }
}


int main() {
  cout << "COSC 1337 Exam 1 Lab Portion" << endl;
  
  /*
    step 1 testing (2 of 10 points) Provide the correct arguments to the area functions
    below, so they  call the correct area function written above for step 1.
    You can create temporary variables, use static_cast, or use type literals
    to get the arguments to be the correct types.
  */
  
  cout<< "\nstep 1: Area of various shapes, using overloaded functions:\n";
  cout<<"  square area for side of 2.2 is: " << area(2.2f) << endl;
  cout<<"  circle area for radius of 3.3 is: " << area(3.3) << endl;
  cout<<"  rectangle area for rectangle of 4.4 height, 5.5 width is: " << area(4.4f, 5.5f) << endl;
  cout<<"  triangle area for triangle of 6.6 wide and 7.7 tall is: " << area(6.6, 7.7) << endl;


  /*
    step 2 testing (2 of 10 points) Provide the correct arguments to the area function
    written for step 2, so it computes the correct area. The same area function
    will be called for all shape types.
  */

  cout<< "\nstep 2: Area of various shapes, based on shape type:\n";
  cout<<"  square area for side of 2.2 is: " << area(Square, 2.2) << endl;
  cout<<"  circle area for radius of 3.3 is: " << area(Circle, 3.3) << endl;
  cout<<"  rectangle area for rectangle of 4.4 height, 5.5 width is: " << area(Rectangle, 4.4, 5.5) << endl;
  cout<<"  triangle area for triangle of 6.6 wide and 7.7 tall is: " << area(Triangle, 6.6, 7.7) << endl;


  /*
    step 3 testing (5 of 10 points) Provide the correct arguments to the stats function
    written for step 3, so it computes the correct statistical values. Then output
    the result for the user to see. Use 10 and 100 as the test input numbers.
  */

  cout<< "\nstep 3: Statistics on a pair of numbers:\n";
  int num1 {10};
  int num2 {100};
  int min, max, sum, dif, avg;
  stats(num1, num2, min, max, sum, dif, avg);
  cout << "  num1=" << num1 << " num2=" << num2 << " min=" << min << " max=" << max << " sum=" << sum << " dif=" << dif
       << " avg=" << avg << endl;

  /*
    step 4 (2 of 10 points for testing) call to get_num() goes here ---
    Test get_num. Call get_num once. Get a number within some valid range. Here are some ideas:
    hour(0..23), month(1..12), inches(1..36), weekday(1..7), temp(-20..120), fingers(1..5)
    Pick one of these examples, or make up one of your own. Test get_num once.
    Save a variable containing the return value from get_num, and display that variable.
    Example: "The month is: 6"
  */

  cout<< "\nstep 4: Return value from get_num:\n";
  double result = get_num<double>(1, 12, "Enter month (1-12): ", "Not a number, try again");
  cout<<"  The month is: "<< result <<endl;

  step6(); // Uncomment if you do step 6

  cout<<endl<<"Goodbye!"<<endl; // this should appear as the last line of your output
  
  return EXIT_SUCCESS; // Use return 0 if EXIT_SUCCESS is undefined
}

/*
  Paste your test output below.  2 point DEDUCTION if no test output.

COSC 1337 Exam 1 Lab Portion

step 1: Area of various shapes, using overloaded functions:
  square area for side of 2.2 is: 4.84
  circle area for radius of 3.3 is: 34.2119
  rectangle area for rectangle of 4.4 height, 5.5 width is: 24.2
  triangle area for triangle of 6.6 wide and 7.7 tall is: 25.41

step 2: Area of various shapes, based on shape type:
  square area for side of 2.2 is: 4.84
  circle area for radius of 3.3 is: 34.2119
  rectangle area for rectangle of 4.4 height, 5.5 width is: 24.2
  triangle area for triangle of 6.6 wide and 7.7 tall is: 25.41

step 3: Statistics on a pair of numbers:
  num1=10 num2=100 min=10 max=100 sum=110 dif=90 avg=55

step 4: Return value from get_num:
Enter month (1-12): june
  Not a number, try again
Enter month (1-12): 0
  Not in range, do-over
Enter month (1-12): 13
  Not in range, do-over
Enter month (1-12): 6
  The month is: 6

step 6 (EC): Statement of conviction:
 One more line of code and I am outta here.

Goodbye!
*/
