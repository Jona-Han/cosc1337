/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 3: Math tutor program/quiz using random number generator
 */

#include <iostream>
#include <cstdlib>

using namespace std;

const int MAX_VALUE {100};

int main ()
{
    cout << "Welcome to the third grade made quiz: \n" << "How many questions would you like?: ";

    int number_of_questions {};
    while (!(cin >> number_of_questions) or (number_of_questions <= 0))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a positive whole number to continue: ";
    }

    cout << "(You may enter a negative number at any time to quit the program)\n";

    //Set seed
    int seed = time(0);
    srand(seed);

    //Ask questions
    float num_correct {0};
    int num_answered {number_of_questions};
    for (int counter = 1; counter <= number_of_questions; counter++)
    {
        //Create questions
        int first_random = rand() % MAX_VALUE;
        int second_random = rand() % (MAX_VALUE - first_random);
        int question_answer = first_random + second_random;

        cout << "\n" << "Q #" << counter << " of " << number_of_questions << ": " << first_random << " + "
            << second_random << "? ";

        //Get user input
        int user_answer {};
        cin >> user_answer;

        //Check user input
        if (user_answer == question_answer)
        {
            cout << "Correct. Good Job!" << "\n";
            num_correct++;
            continue;
        }
        else if (user_answer < 0)
        {
            num_answered = counter - 1;
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Sorry, incorrect! The correct answer was " << question_answer << ".\n";
            continue;
        }
    }
    //Print score
    if (num_answered == 0)
    {
        cout << "\nYour score is: " << num_correct << " of " << num_answered << " for "
             << "0%.\n" << "Goodbye!" << endl;
    }
    else
    {
        cout << "\nYour score is: " << num_correct << " of " << num_answered << " for "
             << num_correct / num_answered * 100 << "%.\n" << "Goodbye!" << endl;
    }
}