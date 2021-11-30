/*
  Programmer:
  Assignment:           Lab 7
  Topic:                Implement and test class Item
  File Name:            DL5_L7_Han.cpp
  Course/Section:       COSC 1337; Section 5
  Due Date:             See syllabus or blackboard
  Instructor:           Thayer
*/

// Compiler directives
#include <iostream> // for cin, cout, endl
#include <fstream>  // if needed for file IO
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class CaseFan {
    private:
        string name;
        int size;
        int rpm;
        float decibels;
        double flowRate;

    public:
        CaseFan();
        CaseFan(string, int, int, float, double);

        void setName(string);
        void setSize(int);
        void setRpm(int);
        void setDecibels(float);
        void setFlowRate(double);

        string getName();
        int getSize();
        int getRpm();
        float getDecibels();
        double getFlowRate();
        double getDbPerFlowRate();
        void show();
};

CaseFan::CaseFan() {
    name = " ";
    size = 0;
    rpm = 0;
    decibels = 0;
    flowRate = 0;
}

CaseFan::CaseFan(string name, int size=0, int rpm=0, float decibels=0, double rate = 0){
    setName(name);
    setSize(size);
    setRpm(rpm);
    setDecibels(decibels);
    setFlowRate(rate);
}

inline void CaseFan::setName(string input) {
    name = input;
}

void CaseFan::setSize(int value) {
    vector <int>PossibleSizes {200, 140, 120, 92, 80, 60, 40};
    if (find(PossibleSizes.begin(), PossibleSizes.end(), value) != PossibleSizes.end()) {
        size = value;
    } else if (find(PossibleSizes.begin(), PossibleSizes.end(), size) == PossibleSizes.end()){
        size = 0;
    }
}

void CaseFan::setRpm(int value) {
    if (value >= 0) {
        rpm = value;
    } else if (!(rpm >= 0)){
        rpm = 0;
    }
}

void CaseFan::setDecibels(float value) {
    if (value >= 0 && value <= 150) {
        decibels = value;
    } else if (!(decibels >= 0 && decibels <= 150)){
        decibels = 0;
    }
}

void CaseFan::setFlowRate(double value) {
    if (value >= 0) {
        flowRate = value;
    } else if (!(flowRate >= 0)){
        flowRate = 0.0;
    }
}

inline string CaseFan::getName() {return name;}
inline int CaseFan::getSize() {return size;}
inline int CaseFan::getRpm() {return rpm;}
inline float CaseFan::getDecibels() {return decibels;}
inline double CaseFan::getFlowRate() {return flowRate;}
inline double CaseFan::getDbPerFlowRate() {return decibels/flowRate;}

void CaseFan::show() {
    cout << "Name:" << name << ", Size:" << size << "mm, RPM:" << rpm << ", Decibels/A:" << decibels
         << ", Flow Rate(mm3/h):" << flowRate << endl;
}


int main() {
  cout << "This program creates at least 5 separate, co-existing instances of a "
          "custom designed object.\nInformation about each object is displayed.\n"
          "Each constructor, setter and getter is tested at least once.\n";

  // Test code goes here. Construct objects with valid and invalid data.
  // Verify that each constructor, setter and getter was executed at least once.
  CaseFan fan1 = CaseFan("Noctua NF-A15 PWM", 140, 1200, 19.2, 115.5);
  CaseFan fan2 = CaseFan("Noctua NF-A12x25 PWM", 120, 2000, 22.6, 102.1);
  CaseFan fan3 = CaseFan("Noctua NF-A9 PWM", 92, 2000, 22.8, 78.9);
  CaseFan fan4 = CaseFan("Invalid Fan", 24, 1500, -3, 75);
  CaseFan fan5 = CaseFan("Impossible Fan", 200, -2000, 170, -0.5);

  fan1.show();
  fan2.show();
  fan3.show();
  fan4.show();
  fan5.show();

  cout << "\nThis ends the class design, implementation, test program. Goodbye.\n";
    return EXIT_SUCCESS;
}   // end of main


// Test output below:
/*

*/
