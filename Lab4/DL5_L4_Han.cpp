/*
Author: Jonathan Han; Course: COSC 1337 Fall 2021 DL5; Instructor: Thayer
Lab 4: Burger shop order application. Keeps track of items, calories, price. Uses single item addition and subtraction
 modes.
 */

#include <iostream>
#include <iomanip>
using namespace std;

//Initial item input mode
enum Mode {Add, Subtract};
Mode current_input_mode = Add;

//Prototypes
float addOrRemove(int num_items, float value);
void printCurrentMode();

int main()
{
    cout << "Place your order from Han-dsome Burger Joint. This app shows your calories and cost as "
            "\nyou add items to your food order. You can clear, order, or quit at any time." << endl;

    //Calories and prices for menu items. Located here to easily update calories or prices.
    const int cal_hamburger = 394;
    const int cal_fries = 386;
    const int cal_soda = 150;
    const int cal_brownie = 132;
    const float price_hamburger = 2.35;
    const float price_fries = 1.65;
    const float price_soda = 1.65;
    const float price_brownie = 1.00;

    //Enumerated data type for possible user selected options and selection mode
    enum Options {Hamburger = 'H', Fries = 'F', Soda = 'S', Brownie = 'B', Clear = 'C', Order = 'O', Quit = 'Q',
                  Addition = '+', Subtraction = '-'};

    //Variables for counting number of items, cost, and calories
    int total_calorie, num_hamburger, num_fries, num_soda, num_brownie;
    total_calorie = num_hamburger = num_fries = num_soda = num_brownie = 0;
    float total_cost {0};

    //Main loop
    while (true)
    {
        cout << "\nCurrent order: Hamburger:" << num_hamburger << " Fries:" << num_fries << " Soda:" << num_soda
             << " Brownie:" << num_brownie << " TOTAL Calories:" << total_calorie << " TOTAL Cost:$" << fixed
             << setprecision(2) << total_cost << ".\n";
        printCurrentMode();
        cout << "Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit: \n";

        //Get user input and convert input to enumerated user_option
        char user_input{};
        cin >> user_input;
        Options user_option = static_cast<Options>(toupper(user_input));

        //Check user selected option. Update number of items, total calories, and total cost
        switch (user_option)
        {
            case Hamburger:
                total_calorie += addOrRemove(num_hamburger, cal_hamburger);
                total_cost += addOrRemove(num_hamburger, price_hamburger);
                num_hamburger += addOrRemove(num_hamburger, 1);
                break;
            case Fries:
                total_calorie += addOrRemove(num_fries, cal_fries);
                total_cost += addOrRemove(num_fries, price_fries);
                num_fries += addOrRemove(num_fries, 1);
                break;
            case Soda:
                total_calorie += addOrRemove(num_soda, cal_soda);
                total_cost += addOrRemove(num_soda, price_soda);
                num_soda += addOrRemove(num_soda, 1);
                break;
            case Brownie:
                total_calorie += addOrRemove(num_brownie, cal_brownie);
                total_cost += addOrRemove(num_brownie, price_brownie);
                num_brownie += addOrRemove(num_brownie, 1);
                break;
            case Clear:
                total_calorie = total_cost = num_hamburger = num_fries = num_soda = num_brownie = 0;
                break;
            case Order: //Check that there is at least 1 item in order and send order
                if (total_cost == 0)
                {
                    cout << "\nPlease input items into your order before ordering.";
                    break;
                }
                else
                {
                    cout << "Thank you for ordering! Your order is being sent. Your total cost is $" << fixed
                         << setprecision(2) << total_cost << ". See you soon!\n";
                    exit(EXIT_SUCCESS);
                }
            case Addition: //Switch to item addition mode
                current_input_mode = Add;
                break;
            case Subtraction: //Switch to item removal mode
                current_input_mode = Subtract;
                break;
            case Quit:
                cout << "Sorry we couldn't serve you this time! Hope to see you again soon.\n";
                exit(EXIT_SUCCESS);
            default: //Input validation
                cout << "\nInvalid input.";
                break;
        }
    }
}

//General function to return +value in Addition mode, -value in Subtraction mode, or 0 if number of items is zero
float addOrRemove(int num_items, float value)
{
    switch (current_input_mode)
    {
        case Add:
            return value;
        case Subtract:
            return (num_items > 0) ? -value : 0;
    }
}

//Print current input mode statement
void printCurrentMode()
{
    switch (current_input_mode)
    {
        case Add:
            cout << "You are currently in item Addition mode. Enter '-' to switch to item Removal mode.\n";
            break;
        case Subtract:
            cout << "You are currently in item Removal mode. Enter '+' to switch to item Addition mode.\n";
            break;
    }
}

/*
Test output:
./DL5_L4_Han
Place your order from Han-dsome Burger Joint. This app shows your calories and cost as
you add items to your food order. You can clear, order, or quit at any time.

Current order: Hamburger:0 Fries:0 Soda:0 Brownie:0 TOTAL Calories:0 TOTAL Cost:$0.00.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
h

Current order: Hamburger:1 Fries:0 Soda:0 Brownie:0 TOTAL Calories:394 TOTAL Cost:$2.35.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
f

Current order: Hamburger:1 Fries:1 Soda:0 Brownie:0 TOTAL Calories:780 TOTAL Cost:$4.00.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
s

Current order: Hamburger:1 Fries:1 Soda:1 Brownie:0 TOTAL Calories:930 TOTAL Cost:$5.65.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
b

Current order: Hamburger:1 Fries:1 Soda:1 Brownie:1 TOTAL Calories:1062 TOTAL Cost:$6.65.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
-

Current order: Hamburger:1 Fries:1 Soda:1 Brownie:1 TOTAL Calories:1062 TOTAL Cost:$6.65.
You are currently in item Removal mode. Enter '+' to switch to item Addition mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
b

Current order: Hamburger:1 Fries:1 Soda:1 Brownie:0 TOTAL Calories:930 TOTAL Cost:$5.65.
You are currently in item Removal mode. Enter '+' to switch to item Addition mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
s

Current order: Hamburger:1 Fries:1 Soda:0 Brownie:0 TOTAL Calories:780 TOTAL Cost:$4.00.
You are currently in item Removal mode. Enter '+' to switch to item Addition mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
s

Current order: Hamburger:1 Fries:1 Soda:0 Brownie:0 TOTAL Calories:780 TOTAL Cost:$4.00.
You are currently in item Removal mode. Enter '+' to switch to item Addition mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
c

Current order: Hamburger:0 Fries:0 Soda:0 Brownie:0 TOTAL Calories:0 TOTAL Cost:$0.00.
You are currently in item Removal mode. Enter '+' to switch to item Addition mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
+

Current order: Hamburger:0 Fries:0 Soda:0 Brownie:0 TOTAL Calories:0 TOTAL Cost:$0.00.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
hh

Current order: Hamburger:1 Fries:0 Soda:0 Brownie:0 TOTAL Calories:394 TOTAL Cost:$2.35.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:

Current order: Hamburger:2 Fries:0 Soda:0 Brownie:0 TOTAL Calories:788 TOTAL Cost:$4.70.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
p

Invalid input.
Current order: Hamburger:2 Fries:0 Soda:0 Brownie:0 TOTAL Calories:788 TOTAL Cost:$4.70.
You are currently in item Addition mode. Enter '-' to switch to item Removal mode.
Choose: H)amburger F)ries S)oda B)rownie C)lear O)rder Q)uit:
o
Thank you for ordering! Your order is being sent. Your total cost is $4.70. See you soon!
*/



