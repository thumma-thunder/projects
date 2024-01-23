#include <iostream>
#include "Player.h"
#include <string>
using namespace std;

void playRockPaperScissors(Player players[2])
{
    bool zeroone;
    string bet1;
    string bet2;
    string choice1;
    string choice2;
    string bet10="";
    string bet20="";
    Candy Bet2;
    Candy Bet1;
    if (players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0)
    {
        cout << "Not enough candy!" << endl;
    }
    else
    {
        cout << "Player 1 Inventory" << endl;
        players[0].printInventory();
        cout << "Player 1: Select candy to bet" << endl;
        getline(cin, bet1);
        while (cin.fail())
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            getline(cin, bet1);
            cin.ignore(1000000, '\n');
        }
        bet10=bet1;
        for (unsigned int j = 0; j < bet1.length(); j++)
        {
            bet10[j] = tolower(bet1[j]);
        }
        Bet1 = players[0].findCandy(bet1);
        while (bet10 != Bet1.name)
        {
            cout << "Invalid selection!" << endl;
            getline(cin, bet1);
            bet10=bet1;
            for (unsigned int j = 0; j < bet1.length(); j++)
            {
                bet10[j] = tolower(bet1[j]);
            }
            Bet1 = players[0].findCandy(bet1);
        }
        cout << "Player 2 Inventory" << endl;
        players[1].printInventory();
        cout << "Player 2: Select candy to bet" << endl;
        getline(cin, bet2);
        while (cin.fail())
        {
            cin.ignore(1000000, '\n');
            cout << "Invalid selection!" << endl;
            cin.clear();
            getline(cin, bet2);
            cin.ignore(1000000, '\n');
        }
        bet20=bet2;

        for (unsigned int j = 0; j < bet2.length(); j++)
        {
            bet20[j] = tolower(bet2[j]);
        }
        Bet2 = players[1].findCandy(bet2);
        while (bet20 != Bet2.name)
        {
            cout << "Invalid selection!" << endl;
            getline(cin, bet2);
            bet20=bet2;
            for (unsigned int j = 0; j < bet2.length(); j++)
            {
                bet20[j] = tolower(bet2[j]);
            }
            Bet2 = players[1].findCandy(bet2);
        }
        cout << "Player 1: Enter r, p, or s" << endl;
        getline(cin, choice1);

        while (choice1 != "r" && choice1 != "p" && choice1 != "s")
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            getline(cin, choice1);
        }
        cout << "Player 2: Enter r, p, or s" << endl;
        getline(cin, choice2);
        while (choice2 != "r" && choice2 != "p" && choice2 != "s")
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            getline(cin, choice2);
        }
        while (choice1 == choice2)
        {
            cout << "Tie! Play again" << endl;
            cout << "Player 1: Enter r, p, or s" << endl;
            getline(cin, choice1);

            while (choice1 != "r" && choice1 != "p" && choice1 != "s")
            {
                cout << "Invalid selection!" << endl;
                cin.clear();
                getline(cin, choice1);
            }
            cout << "Player 2: Enter r, p, or s" << endl;
            getline(cin, choice2);
            while (choice2 != "r" && choice2 != "p" && choice2 != "s")
            {
                cout << "Invalid selection!" << endl;
                cin.clear();
                getline(cin, choice2);
            }
        }
        if ((choice1 == "r" && choice2 == "s") || (choice1 == "p" && choice2 == "r") || (choice1 == "s" && choice2 == "p"))
        {
            zeroone = false;
        }
        else if ((choice1 == "r" && choice2 == "p") || (choice1 == "p" && choice2 == "s") || (choice1 == "s" && choice2 == "r"))
        {
            zeroone = true;
        }

        if (zeroone == false)
        {
            string pls1 = Bet2.name;
            cout << "Player 1 has won " << bet2 << " from player 2!" << endl;
            players[1].removeCandy(pls1);
            players[0].addCandy(Bet2);
        }
        else
        {
            string pls2 = Bet1.name;
            cout << "Player 2 has won " << bet1 << " from player 1!" << endl;
            players[0].removeCandy(pls2);
            players[1].addCandy(Bet1);
        }
    }
}

int main()
{

    Candy cd = {"brown candy", "bronco", 0.0, "bronco"};
    Candy dd = {"striped candy", "bronco", 0.0, "bronco"};
    Candy cc = {"yellow candy", "bronco", 0.0, "bronco"};

    Candy c[] = {cd, dd, cc};
    Player player = {"Lebron", "Tottle_todd", 1, 1.1, "poop", c, 3};
    Player player2 = {"Curry", "FRAUD",1, 1.1, "poop", c, 3};

    Player players[2] = {player, player2};
    cout << players[0].getCandyAmount() << endl;
    playRockPaperScissors(players);
    cout << "Player 1 Inventory After:" << endl;
    players[0].printInventory();

    cout << "Player 2 Inventory After:" << endl;
    players[1].printInventory();
}