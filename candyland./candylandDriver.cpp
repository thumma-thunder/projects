#include <iostream>
#include "Player.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;
vector<Candy> readCandy(string file_name, vector<Candy> candies)
{
    string line;
    string name;
    string description;
    string price;
    string candy_type;
    double prices;
    ifstream file(file_name);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line != "")
            {
                stringstream ss(line);
                getline(ss, name, '|');
                getline(ss, description, '|');
                getline(ss, price, '|');
                getline(ss, candy_type);
                Candy temp;
                temp.name = name;
                temp.description = description;
                prices = stod(price);
                temp.price = prices;
                temp.candy_type = candy_type;

                candies.push_back(temp);
            }
        }
        file.close();
    }
    else
    {
        cout << "Failed to open file" << endl;
    }
    return candies;
}
void playRockPaperScissors(Player players[])
{
    bool zeroone;
    string bet1;
    string bet2;
    string choice1;
    string choice2;
    string bet10 = "";
    string bet20 = "";
    Candy Bet2;
    Candy Bet1;
    string bet1name;
    string bet2name;
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
        bet10 = bet1;
        for (unsigned int j = 0; j < bet1.length(); j++)
        {
            bet10[j] = tolower(bet1[j]);
        }
        Bet1 = players[0].findCandy(bet1);
        bet1name = Bet1.name;
        for (unsigned int j = 0; j < Bet1.name.length(); j++)
        {
            bet1name[j] = tolower(Bet1.name[j]);
        }
        while (bet10 != bet1name)
        {
            cout << "Invalid selection!" << endl;
            getline(cin, bet1);
            bet10 = bet1;
            for (unsigned int j = 0; j < bet1.length(); j++)
            {
                bet10[j] = tolower(bet1[j]);
            }
            Bet1 = players[0].findCandy(bet1);
            bet1name = Bet1.name;
            for (unsigned int j = 0; j < Bet1.name.length(); j++)
            {
                bet1name[j] = tolower(Bet1.name[j]);
            }
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
        bet20 = bet2;

        for (unsigned int j = 0; j < bet2.length(); j++)
        {
            bet20[j] = tolower(bet2[j]);
        }
        Bet2 = players[1].findCandy(bet2);
        bet2name = Bet2.name;
        for (unsigned int j = 0; j < Bet2.name.length(); j++)
        {
            bet2name[j] = tolower(Bet2.name[j]);
        }
        while (bet20 != bet2name)
        {
            cout << "Invalid selection!" << endl;
            getline(cin, bet2);
            bet20 = bet2;
            for (unsigned int j = 0; j < bet2.length(); j++)
            {
                bet20[j] = tolower(bet2[j]);
            }
            Bet2 = players[1].findCandy(bet2);
            bet2name = Bet2.name;
            for (unsigned int j = 0; j < Bet2.name.length(); j++)
            {
                bet2name[j] = tolower(Bet2.name[j]);
            }
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
            cout << "Player 1 has won " << bet2 << " from player 2!" << endl;
            players[1].removeCandy(bet2name);
            players[0].addCandy(Bet2);
        }
        else
        {
            cout << "Player 2 has won " << bet1 << " from player 1!" << endl;
            players[0].removeCandy(bet1name);
            players[1].addCandy(Bet1);
        }
    }
}

void printCandies(vector<Candy> candies)
{
    int size = candies.size();
    for (int i = 0; i < size; i++)
    {
        cout << "Name: " << candies[i].name << ". Description: " << candies[i].description << fixed << setprecision(2) << ". Price: " << candies[i].price << ". Type: " << candies[i].candy_type << endl;
    }
}

void printPlayer(Player player)
{

    cout << "Stamina: " << player.getStamina() << endl;
    cout << "Gold: " << fixed << setprecision(2) << player.getGold() << endl;
    cout << "Effect: " << player.getEffect() << endl;
    cout << "Inventory: " << endl;
    player.printInventory();
}

Player editPlayer(Player player, vector<Candy> options, int play)
{
    int size = options.size();
    int choice;
    string effect;
    string option;
    string oppo;
    string remove;
    bool gone;
    cout << "1. Edit stamina" << endl
         << "2. Edit gold" << endl
         << "3. Edit effect" << endl
         << "4. Add candy" << endl
         << "5. Remove candy" << endl;
    cin >> choice;
    while (choice < 1 || choice > 5)
    {
        cout << "Invalid input!" << endl;
        cin.clear();
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        int stam;
        cout << "Editing stamina. Enter a value between 1 and 10:" << endl;
        cin >> stam;
        while ((stam < 1 || stam > 10) || cin.fail())
        {
            if (cin.fail())
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(1000000, '\n');
                cin >> stam;
            }
            else
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin >> stam;
            }
        }
        player.setStamina(stam);
        break;
    case 2:
        double gold;
        cout << "Editing gold. Enter a value between 0 and 1000:" << endl;
        cin >> gold;
        while ((gold < 0 || gold > 1000) || cin.fail())
        {
            if (cin.fail())
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(1000000, '\n');
                cin >> gold;
            }
            else
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin >> gold;
            }
        }
        player.setGold(gold);
        break;
    case 3:
        cout << "Editing effect. Enter the name of an effect as a string:" << endl;
        cin.ignore(1000000, '\n');
        getline(cin, effect);
        while (cin.fail())
        {
            cout << "Invalid input!" << endl;
            cin.clear();
            getline(cin, effect);
        }
        player.setEffect(effect);
        break;
    case 4:
        if (options.size() == 0)
        {
            cout << "Cannot add candy! Read a candy file first" << endl;
        }
        else
        {
            cout << "Adding candy. Enter one of the following options:" << endl;
            printCandies(options);

            bool validOption = false;
            cin.ignore(1000000, '\n');
            while (!validOption)
            {
                getline(cin, option);
                while (cin.fail())
                {
                    cout << "Invalid input!" << endl;
                    cin.clear();
                    getline(cin, option);
                    cin.ignore(1000000, '\n');
                }
                
                for (unsigned int i = 0; i < option.length(); i++)
                {
                    option[i] = tolower(option[i]);
                }
                for (int i = 0; i < size; i++)
                {
                    oppo = options[i].name;
                    for (unsigned int j = 0; j < options[i].name.length(); j++)
                    {
                        oppo[j] = tolower(options[i].name[j]);
                    }

                    if (option == oppo)
                    {
                        player.addCandy(options[i]);
                        validOption = true;
                        break;
                    }
                }
                if (!validOption)
                {
                    cout << "Invalid input!" << endl;
                }
            }
        }
        break;
    case 5:
        cout << "Removing candy. Enter the name of a candy in player " << play << "'s inventory:" << endl;
        player.printInventory();
        cin.ignore(1000000, '\n');
        getline(cin, remove);
        while (cin.fail())
        {
            cout << "Invalid input!" << endl;
            cin.clear();
            getline(cin, remove);
            cin.ignore(1000000, '\n');
        }

        gone = player.removeCandy(remove);
        while (gone == false)
        {
            cout << "Invalid input!" << endl;
            getline(cin, remove);
            while (cin.fail())
            {
                cout << "Invalid input!" << endl;
                cin.clear();
                getline(cin, remove);
                cin.ignore(1000000, '\n');
            }
            gone = player.removeCandy(remove);
        }
        break;
    }
    return player;
}
int main()
{
    int choice;
    bool run = true;
    vector<Candy> options;
    string file;
    Player player;
    string display;
    string edit;
    Player player1;
    Player player2;
    Player players[2];
    players[0] = player1;
    players[1] = player2;
    cout << "Welcome to rock-paper-scissors, candy edition!" << endl
         << "Choose an option:" << endl
         << "1. Load Candy" << endl
         << "2. Display player stats " << endl
         << "3. Edit player stats " << endl
         << "4. Play rock-paper-scissors" << endl
         << "5. Exit" << endl;
    cin >> choice;
    cin.ignore(1000000, '\n');
    while (run == true)
    {
        while ((choice > 5 || choice < 1) || cin.fail())
        {
            cout << "Invalid input!" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            cin >> choice;
            cin.ignore(1000000, '\n');
        }
        switch (choice)
        {
        case 1:
            cout << "Enter file to read:" << endl;
            cin >> file;
            options = readCandy(file, options);
            break;
        case 2:
            cout << "Which player's stats do you want to display? Choose 1 or 2:" << endl;
            cin.clear();
            getline(cin, display);
            while (display != "1" && display != "2")
            {
                cout << "Invalid input" << endl;
                cin.clear();
                cin >> display;
            }

            if (display == "1")
            {
                cout << "Player 1 stats:" << endl;
                printPlayer(players[0]);
            }
            else
            {
                cout << "Player 2 stats:" << endl;
                printPlayer(players[1]);
            }
            break;
        case 3:
            cout << "Which player's stats do you want to edit? Choose 1 or 2:" << endl;
            getline(cin, edit);
            while (edit != "1" && edit != "2")
            {
                cout << "Invalid input" << endl;
                cin.clear();
                cin >> edit;
            }
            if (edit == "1")
            {
                cout << "Editing player 1 stats:" << endl;
                players[0] = editPlayer(players[0], options, 1);
            }
            else
            {
                cout << "Editing player 2 stats:" << endl;
                players[1] = editPlayer(players[1], options, 2);
            }
            break;
        case 4:

            playRockPaperScissors(players);
            break;
        case 5:
            run = false;
            break;
        }
        if (run == true)
        {
            cout << "Choose an option:" << endl
                 << "1. Load Candy" << endl
                 << "2. Display player stats " << endl
                 << "3. Edit player stats " << endl
                 << "4. Play rock-paper-scissors" << endl
                 << "5. Exit" << endl;
            cin >> choice;
            cin.ignore(1000000, '\n');
        }
    }
}