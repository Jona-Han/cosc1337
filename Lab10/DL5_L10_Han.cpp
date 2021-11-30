/*
  Author: Jonathan Han
  Assignment:      Lab 10
  Topic:           memory diagram with stack, heap structures
  Course/Section:  COSC 1337
  Due Date:        See syllabus or blackboard
  Instructor:      Thayer
  Purpose:
  This lab is on pointers. It covers: values, addresses, pointers, the heap,
  dynamic memory allocation using new, delete, delete [].
  It also has a brief introduction to linked lists, a basic data structure.

  Create a program that uses memory as shown in the memory diagram provided.
  Start with this startup code, which has useful macros to display variables.
*/

#include <iostream>
#include <iomanip>
using namespace std;

class Number { // modify class Number if desired to provide constructors, etc.
public:
    string name;     // name of the Number
    Number *next;    // pointer to the next Number in the list

    Number(string name, Number* next = nullptr) {
        this->name = name;
        this->next = next;
    }
};

// Helpful macros to make it easier to output name, address, and value of a variable
// You may use these, or write your own function that does something similar
#define show_addr_value(var, width) \
  cout<<"address of " <<setw(width)<<left<<#var<<" is: &"<<&var<<"  "     \
      <<"contents of "<<setw(width)<<left<<#var<<" is: "<<var<<endl;

#define show_addr(var, width) \
  cout<<"address of " <<setw(width)<<left<<#var<<" is: &"<<&var<<endl;

int main () {
    const int WIDTH = 8;
    cout << "Output from Lab10 memory diagram on pointers:\n\n";

    float price = 0;
    float *p_price = &price;
    *p_price = 18.65;
    show_addr_value(price, WIDTH);
    show_addr_value(p_price, WIDTH);
    cout << "The contents of *p_price is: " << *p_price << endl << endl;

    /* Useful output comments, describes results, use as desired.
       You can use show_addr_value and show_addr to show addresses and values;
       You can use cout messages below to provide more detailed messages.
       See sample of full solution output in the instructions.
    */

    //Assign PI on stack, create a pointer to PI, dereference pointer to assign PI divided by 2
    double PI, *p_PI;
    p_PI = &PI;
    *p_PI = 3.141592;
    double PI_div_2 = *p_PI / 2;
    show_addr_value(PI, WIDTH);
    show_addr_value(p_PI, WIDTH);
    show_addr_value(PI_div_2, WIDTH);
    cout << "The contents of *p_PI is:    " << *p_PI << endl << endl;

    //Declare ACCeID on stack, use pointer to give ACCeID a value
    int ACCeID, *p_ACCeID;
    p_ACCeID = &ACCeID;
    *p_ACCeID = 2199222;
    show_addr_value(ACCeID, WIDTH);
    show_addr_value(p_ACCeID, WIDTH);
    cout << "The contents of *p_ACCeID is: " << *p_ACCeID << endl << endl;

    //Put an integer 2486 on the heap, then delete p_amount and set it to a null pointer
    int* p_amount = new int(2486);
    show_addr_value(p_amount, WIDTH);
    cout << "The contents of *p_amount is: " << (dec) << *p_amount << endl;

    delete p_amount;
    cout << "After delete, the contents of p_amount is: " << p_amount << endl;
    p_amount = nullptr;
    cout << "After reset to nullptr, the contents of p_amount is: " << p_amount << endl << endl;

    //Create an array of 3 integers on the heap, delete the whole array and set it to a null pointer
    int* pArray1 = new int[3];
    pArray1[0] = 100;
    pArray1[1] = 200;
    *(pArray1 + 2) = 300;
    show_addr_value(pArray1, WIDTH);
    show_addr_value(pArray1[0], WIDTH);
    show_addr_value(pArray1[1], WIDTH);
    show_addr_value(pArray1[2], WIDTH);

    delete [] pArray1;
    cout << "After delete [], the contents of pArray is: " << pArray1 << endl;
    pArray1 = nullptr;
    cout << "After reset to nullptr, the contents of pArray1 is: " << pArray1 << endl << endl;

    //Create an array on the stack and a pointer pointing to the first element of the array
    int Array2[2] = {1111, 2222};
    int* pArray2 = &Array2[0];
    show_addr_value(pArray2, WIDTH);
    show_addr_value(pArray2[0], WIDTH);
    show_addr_value(pArray2[1], WIDTH);
    cout << "No need to delete Array2, it is on the stack, not the heap" << endl << endl;

    //Create a large array of doubles on the heap, delete this array and set it to a null pointer.
    double* big_buffer = new double[2199222];
    show_addr_value(big_buffer, WIDTH);
    delete [] big_buffer;
    cout << "After delete [], the contents of big_buffer is: " << big_buffer << endl;
    big_buffer = nullptr;
    cout << "After reset to nullptr, the contents of big_buffer is: " << big_buffer << endl << endl;

    //Create a Number pointer that points to null
    Number* emptyList = nullptr;
    show_addr_value(emptyList, WIDTH);
    cout << endl;

    //Create a Number object on the stack
    cout<<"static (uses: Number zed):\n";
    Number zed = Number("Zero");
    show_addr(zed, WIDTH);
    show_addr_value(zed.name, WIDTH);
    show_addr_value(zed.next, WIDTH);
    cout << endl;

    //Create a linked list of number objects on the heap
    cout<<"dynamic (uses: p_natural, Number(\"Two\"), Number(\"One\"):\n";
    Number* pNatural = new Number("Two", new Number("One"));
    show_addr_value(pNatural, WIDTH);
    show_addr_value(pNatural->name, WIDTH);
    show_addr_value(pNatural->next, WIDTH);
    cout << "Follow link to next Number in linked list;" << endl;
    show_addr_value(pNatural->next->name, WIDTH);
    show_addr_value(pNatural->next->next, WIDTH);

    //Free up memory from the heap starting from the deepest/last element
    delete pNatural->next;
    delete pNatural;

    return 0;
} // end of main

/*
Output from Lab10 memory diagram on pointers:

address of price    is: &0x16cf7f744  contents of price    is: 18.65
address of p_price  is: &0x16cf7f738  contents of p_price  is: 0x16cf7f744
The contents of *p_price is: 18.65

address of PI       is: &0x16cf7f720  contents of PI       is: 3.14159
address of p_PI     is: &0x16cf7f718  contents of p_PI     is: 0x16cf7f720
address of PI_div_2 is: &0x16cf7f710  contents of PI_div_2 is: 1.5708
The contents of *p_PI is:    3.14159

address of ACCeID   is: &0x16cf7f6f4  contents of ACCeID   is: 2199222
address of p_ACCeID is: &0x16cf7f6e8  contents of p_ACCeID is: 0x16cf7f6f4
The contents of *p_ACCeID is: 2199222

address of p_amount is: &0x16cf7f6d0  contents of p_amount is: 0x600002f4c030
The contents of *p_amount is: 2486
After delete, the contents of p_amount is: 0x600002f4c030
After reset to nullptr, the contents of p_amount is: 0x0

address of pArray1  is: &0x16cf7f6c0  contents of pArray1  is: 0x600002f4c030
address of pArray1[0] is: &0x600002f4c030  contents of pArray1[0] is: 100
address of pArray1[1] is: &0x600002f4c034  contents of pArray1[1] is: 200
address of pArray1[2] is: &0x600002f4c038  contents of pArray1[2] is: 300
After delete [], the contents of pArray is: 0x600002f4c030
After reset to nullptr, the contents of pArray1 is: 0x0

address of pArray2  is: &0x16cf7f698  contents of pArray2  is: 0x16cf7f750
address of pArray2[0] is: &0x16cf7f750  contents of pArray2[0] is: 1111
address of pArray2[1] is: &0x16cf7f754  contents of pArray2[1] is: 2222
No need to delete Array2, it is on the stack, not the heap

address of big_buffer is: &0x16cf7f678  contents of big_buffer is: 0x127800000
After delete [], the contents of big_buffer is: 0x127800000
After reset to nullptr, the contents of big_buffer is: 0x0

address of emptyList is: &0x16cf7f668  contents of emptyList is: 0x0

static (uses: Number zed):
address of zed      is: &0x16cf7f640
address of zed.name is: &0x16cf7f640  contents of zed.name is: Zero
address of zed.next is: &0x16cf7f658  contents of zed.next is: 0x0

dynamic (uses: p_natural, Number("Two"), Number("One"):
address of pNatural is: &0x16cf7f600  contents of pNatural is: 0x600002d4c000
address of pNatural->name is: &0x600002d4c000  contents of pNatural->name is: Two
address of pNatural->next is: &0x600002d4c018  contents of pNatural->next is: 0x600002d4c020
Follow link to next Number in linked list;
address of pNatural->next->name is: &0x600002d4c020  contents of pNatural->next->name is: One
address of pNatural->next->next is: &0x600002d4c038  contents of pNatural->next->next is: 0x0

Process finished with exit code 0
*/
