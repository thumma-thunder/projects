

#include "Candystore.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;



bool playRockPaperScissors()
{
    string player1choice;
    string computer_choice;

    cout << "Player: Enter r, p, or s" << endl;
    getline(cin, player1choice);

    while ((cin.fail()) || (player1choice != "r" && player1choice != "p" && player1choice != "s") || (player1choice == "R" || player1choice == "P" || player1choice == "S"))
    {
        cout << "Invalid selection!" << endl;
        cin.clear();
        // cin.ignore(10000, '\n');
        getline(cin, player1choice);
    }
    
    // computer input
    int random = rand() % 3 + 1;

    if (random == 1)
    {
        computer_choice = "r";
    }
    else if (random == 2)
    {
        computer_choice = "p";
    }
    else if (random == 3)
    {
        computer_choice = "s";
    }

    while (player1choice == computer_choice)
    {
        int random1 = rand() % 3 + 1;

        cout << "Tie! Play again" << endl;

    if (random1 == 1)
    {
        computer_choice = "r";
    }
    else if (random1 == 2)
    {
        computer_choice = "p";
    }
    else if (random1 == 3)
    {
        computer_choice = "s";
    }
        cout << "Enter r, p, or s" << endl;
        cin >> player1choice;
    }

    bool bools;
    if ((player1choice == "r" && computer_choice == "s") || (player1choice == "p" && computer_choice == "r") || (player1choice == "s" && computer_choice == "p"))
    {
        bools = true;
    }
    else
    {
        bools = false;
    }

    if (bools == true)
    {
        cout << "Congratulations!" << endl << "You have won!" << endl;
    }
    else if (bools == false)
    {
        cout << "You have lost!" << endl;
        cout << "Better luck next time!" << endl;
    }
}