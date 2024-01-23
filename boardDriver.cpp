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

struct Card
{
    string color;
    bool twox = false;
};

struct Riddle
{
    string riddle;
    string answer;
};

bool playRockPaperScissors()
{
    srand(time(0));
    string player1choice;
    string computer_choice;
    cout << "The candy land gods challenge you to a game of rock paper scissors!" << endl;
    cout << "Player: Enter r, p, or s" << endl;
    cin.clear();
    getline(cin, player1choice);
    while ((cin.fail()) || (player1choice != "r" && player1choice != "p" && player1choice != "s") || (player1choice == "R" || player1choice == "P" || player1choice == "S"))
    {
        cout << "Invalid selection!" << endl;
        cin.clear();
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
        cout << "Tie! You both chose " << player1choice << " Play again" << endl;

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
        cout << "The Candy land gods have chosen " << computer_choice << endl;
        cout << "Congratulations!" << endl
             << "You have won your game of Rock Paper Scissors!" << endl;
        return true;
    }
    else if (bools == false)
    {
        cout << "The Candy land gods have chosen " << computer_choice << endl;
        cout << "You have lost!" << endl;
        cout << ":(" << endl;
        return false;
    }
    return false;
}

vector<Riddle> loadRiddles(string file)
{
    string line;
    string riddle;
    string answer;
    vector<Riddle> riddles;
    ifstream infile(file);
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            stringstream ss(line);
            getline(ss, riddle, '|');
            ss >> answer;
            Riddle t{riddle, answer};
            riddles.push_back(t);
        }
        infile.close();
        return riddles;
    }
    else
    {
        cout << "Could not load riddles, please restart." << endl;
        return riddles;
    }
}

// Loads riddles into a vector of strings using getline

vector<Candy> loadCandies(string file)
{
    vector<Candy> candies;
    ifstream infile(file);
    string line;
    string name;
    string description;
    string effect_type;
    int effect_value;
    string eff;
    string candy_type;
    double price;
    string price_;
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, description, '|');
            getline(ss, effect_type, '|');
            getline(ss, eff, '|');
            getline(ss, candy_type, '|');
            getline(ss, price_, '|');
            effect_value = stoi(eff);
            price = stod(price_);

            Candy C{name, description, effect_type, effect_value, candy_type, price};
            candies.push_back(C);
        }
        return candies;
    }
    cout << "Could not load candies. Please restart game" << endl;
    return candies;
}
// Load all the candies from the file and store them as their own candy structures using getline
// Returns vector of candies
// Name|Description|Effect type|Effect value|Candy type|Price

Candy findCandy(string candy_name, vector<Candy> candie, int candycount)
{
    string test = "";
    for (unsigned int j = 0; j < candy_name.length(); j++)
    {
        candy_name[j] = tolower(candy_name[j]);
    }
    for (int i = 0; i < candycount; i++)
    {
        test = candie[i].name;
        for (unsigned int j = 0; j < candie[i].name.length(); j++)
        {
            test[j] = tolower(candie.at(i).name[j]);
        }
        if (test == candy_name)
        {
            return candie.at(i);
        }
    }
    Candy T;
    return T;
}

void addcandies(vector<string> candynames, Candy candy[], vector<Candy> candie)
{
    int candycount = candynames.size();
    int vectorcount = candie.size();
    for (int i = 0; i < candycount; i++)
    {
        Candy t = findCandy(candynames.at(i), candie, vectorcount);
        if (t.name != "")
        {
            candy[i] = t;
        }
    }
}
// find every candy name string as a candy in the vector of candies that was loaded in
// Add these candies to the candy array

vector<Player> loadCharacters(string file, vector<Candy> candies)
{
    vector<Player> characters;
    ifstream infile(file);
    string name = "";
    string line;
    string charName;
    string stam;
    int stamina;
    string goldie;
    double gold;
    string candy1;
    while (getline(infile, line))
    {
        vector<string> candynames;
        stringstream ss(line);
        getline(ss, charName, '|');
        getline(ss, stam, '|');
        getline(ss, goldie, '|');
        stamina = stoi(stam);
        gold = stod(goldie);
        while (getline(ss, candy1, ','))
        {
            candynames.push_back(candy1);
        }
        int candycount = candynames.size();
        for (int i = 0; i < candycount; i++)
        {
        }
        Candy candiesarray[9]; // Change if max player inventory size changes
        addcandies(candynames, candiesarray, candies);

        Player temp{name, charName, stamina, gold, candiesarray, candycount};
        characters.push_back(temp);
    }
    return characters;
}

// Load atleast 4 characters and return vector of players
// Use getline looping to retrieve all the data from  file
// store candy names as vector of strings, initialize empty array that is the same size as candies in line(vector of candy)
// Pass array of strings and empty candy array along with vector of candies

bool solveRiddle(vector<Riddle> &riddles)
{
    srand(time(0));
    string answer;
    int rid = rand() % riddles.size();
    cout << riddles.at(rid).riddle << endl;
    cin >> answer;
    Riddle temp = riddles.at(rid);
    if (answer == riddles.at(rid).answer)
    {

        for (unsigned int i = rid; i < riddles.size() - 1; i++)
        {
            riddles.at(i) = riddles.at(i + 1);
        }
        riddles.at(riddles.size() - 1) = temp;
        riddles.pop_back();
        cout << "Correct!!!!!" << endl;

        return true;
    }
    for (unsigned int i = rid; i < riddles.size() - 1; i++)
    {
        riddles.at(i) = riddles.at(i + 1);
    }
    riddles.at(riddles.size() - 1) = temp;
    riddles.pop_back();
    cout << "Incorrect answer." << endl;
    return false;
}
// Cout the riddles randomly and return true if they solve it
void rewardTreasure(Player &player)
{
    srand(time(0));
    int random = rand() % 10;
    if (random < 3)
    {
        cout << "You won a stamina refill from the treasure tile!" << endl;
        int stam = (rand() % 21) + 10;
        player.setStamina(player.getStamina() + stam);
        cout << "Your stamina is now " << player.getStamina() << endl;
        return;
    }
    else if (random < 4)
    {
        cout << "A gold windfall is taking place!" << endl;
        int gold = (rand() % 21) + 20;
        player.setGold(player.getGold() + gold);
        cout << "Your gold is now " << player.getGold() << endl;
        return;
    }
    else if (random < 7)
    {
        cout << "You recieved Robber's Rappel! This candy will protect you when you are getting robbed by another player." << endl;
        Candy treasure{"Robber's Rappel", "This candy will protect you when you are getting robbed by another player.", "other", 0, "special", 0};
        if (!player.isInventoryFull())
        {
            player.addCandy(treasure);
            cout << "Here is your updated candy inventory:" << endl;
            player.printInventory();
            return;
        }
        else
        {
            player.swapMenu(treasure);
            return;
        }
    }
    else
    {
        int rand2 = rand() & 10;
        if (rand2 < 3)
        {
            cout << " You retrieved a Treasure Hunter's Truffle from the treasure!" << endl;
            Candy treasure{"Treasure Hunter's Truffle", "This candy allows the player to unlock a hidden treasure.", "treasure", 0, "treasure", 0};
            if (!player.isInventoryFull())
            {
                player.addCandy(treasure);
                cout << "Here is your updated candy inventory:" << endl;
                player.printInventory();
                return;
            }
            else
            {
                player.swapMenu(treasure);
                return;
            }
        }
        else
        {
            cout << "You retrieved a Jellybean of Vigor from the treasure!" << endl;
            Candy treasure{"Jellybean of Vigor", "This special candy offers some amount of stamina regeneration, providing a valuable boost to the player's energy levels", "stamina", 50, "special", 0};
            if (!player.isInventoryFull())
            {
                player.addCandy(treasure);
                cout << "Here is your updated candy inventory:" << endl;
                player.printInventory();
                return;
            }
            else
            {
                player.swapMenu(treasure);
                return;
            }
        }
    }
}

Card drawCard()
{
    srand(time(0));
    Card BubblegumBlue{"Bubblegum Blue", false};
    Card dblBubblegumBlue{"Bubblegum Blue", true};
    Card MintyGreen{"Minty Green", false};
    Card dblMintyGreen{"Minty Green", true};
    Card CottonCandyMagenta{"Cotton Candy Magenta", false};
    Card dblCottonCandyMagenta{"Cotton Candy Magenta", true};

    Card cards[6] = {CottonCandyMagenta, MintyGreen, BubblegumBlue, dblCottonCandyMagenta, dblMintyGreen, dblCottonCandyMagenta};
    int doubleornah = rand() % 10;
    int randomcard = rand() % 3;
    if (doubleornah == 0 || doubleornah == 2)
    {
        return cards[randomcard + 3];
    }
    else
    {
        return cards[randomcard];
    }
}
// srand time stuff to draw a random card, 75% chance of a single card and 25% of double, equal chance between which color you get

int moveTo(int position, Card card)
{

    cout << "You drew a " << card.color << " card!" << endl;
    int oldposition = position;
    int idx;
    if (card.color == "Bubblegum Blue")
    {
        idx = 2;
        while (++position % 3 != idx)
        {
            position++;
            if (position >= 82)
            {
                return 0;
            }
        }
        if (card.twox == false)
        {
            cout << "You moved to the next blue tile!" << endl;
            return position - oldposition;
        }
        else
        {
            cout << "You moved to the second blue tile over!" << endl;
            return (position + 3) - oldposition;
        }
    }
    else if (card.color == "Minty Green")
    {
        idx = 1;
        while (++position % 3 != idx)
        {
            position++;
            if (position >= 82)
            {
                return 0;
            }
        }

        if (card.twox == false)
        {
            cout << "You moved to the next green tile!" << endl;

            return position - oldposition;
        }
        else
        {
            cout << "You moved to the second green tile over!" << endl;
            return (position + 3) - oldposition;
        }
    }
    else
    {
        idx = 0;
        while (++position % 3 != idx)
        {
            position++;
            if (position >= 82)
            {
                return 0;
            }
        }
        if (card.twox == false)
        {
            cout << "You moved to the next magenta tile!" << endl;
            return position - oldposition;
        }
        else
        {
            cout << "You moved to the second magenta tile over!" << endl;
            return (position + 3) - oldposition;
        }
    }
}
// Calulates how much to move and takes old position of player and the card they drew as input
// Use modulus 3 to find out what color tile you are on  (0= magenta 1=green 2=blue)
// return the amount the player needs to move to use setPlayerPosition()

void movePlayer(int idx, Card card, Board &board)
{
    int position = board.getPlayerPosition(idx);
    int newposition = moveTo(position, card);
    if (newposition == 0)
    {
        board.setPlayerPosition(82, idx);
        return;
    }
    board.movePlayer(newposition, idx);
    return;
}
// Calls moveTo() and then movePlayer() to move the player to the new position
Player choosePlayer(vector<Player> &players)
{
    string name;
    cout << "Enter player name: " << endl;
    getline(cin, name);
    while (cin.fail())
    {
        cout << "Invalid name!" << endl;
        cin.clear();
        cin.ignore(1000000, '\n');
        cin >> name;
    }
    cout << "Awesome! Here is a list of characters a player can select from" << endl;
    string choice;
    for (unsigned int i = 0; i < players.size(); i++)
    {
        players[i].displayCharStats();
        cout << "------------------------------" << endl;
    }
    cout << endl
         << "The character selected is" << endl;
    getline(cin, choice);
    bool playerfound = false;
    for (unsigned int i = 0; i < players.size(); i++)
    {
        if (choice == players[i].getCharacter())
        {
            playerfound = true;
        }
    }
    while (cin.fail() || playerfound == false)
    {
        if (cin.fail())
        {
            cout << "Invalid character selection" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            cin >> choice;
            for (unsigned int i = 0; i < players.size(); i++)
            {
                if (choice == players[i].getCharacter())
                {
                    playerfound = true;
                    cin.ignore(1000000, '\n');
                }
            }
        }
        else
        {
            cout << "Invalid character selection" << endl;
            cin >> choice;
            for (unsigned int i = 0; i < players.size(); i++)
            {
                if (choice == players[i].getCharacter())
                {
                    playerfound = true;
                    cin.ignore(1000000, '\n');
                }
            }
        }
    }
    for (unsigned int i = 0; i < players.size(); i++)
    {
        if (choice == players[i].getCharacter())
        {
            Player temp = players[i];
            for (unsigned int j = i; j < players.size() - 1; j++)
            {

                players[j] = players[j + 1];
            }
            players[players.size() - 1] = temp;
            players.pop_back();
            temp.setName(name);
            return temp;
        }
    }
    cout << "No player was selected" << endl;
    Player j;
    return j;
}
/*
call display player for each player(2) and add a break(------)
string choice;
cout << "The character selected is" << endl;
getline(cin, choice);
error handling
algorithm to find player in vector and return them/send them to back to be popped out
*/
void candyStoreMenu(Player &player, Board &board, int position)
{
    cin.clear();
    int candy_store_idx = board.getCandyStoreIndex(position);
    Candystore store = board.getCandystore(candy_store_idx);
    if (store.getCandyCount() == 0)
    {
        cout << "The candy store is out of candy. :(" << endl;
        return;
    }
    char enter;
    if (position != 0)
    {
        cout << "You landed on a tile which has a candy store." << endl;
        cout << endl;
    }
    cout << "Do you want to visit the candy store? (y/n)" << endl;
    cin >> enter;
    while (cin.fail() || (enter != 'y' && enter != 'n'))
    {
        cout << "Invalid selection!" << endl;
        cin.clear();
        cin >> enter;
    }
    if (enter == 'y')
    {

        store.displayCandy();
        cout << "You have " << player.getGold() << " gold. "
             << "Do not choose a candy you cannot afford or you will leave the candy store!" << endl;
        string candy_name;
        cout << "Which candy would you like to buy?" << endl;
        cin.ignore(1000000, '\n');
        getline(cin, candy_name);
        while (cin.fail())
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            getline(cin, candy_name);
        }
        Candy candy = store.findCandy(candy_name);

        while (candy.name == "")
        {
            cout << "Invalid selection! Select a candy from the store to continue." << endl;
            getline(cin, candy_name);

            while (cin.fail())
            {
                cout << "Invalid selection!" << endl;
                cin.clear();
                cin.ignore(1000000, '\n');
                getline(cin, candy_name);
            }
            candy = store.findCandy(candy_name);
        }
        if (player.getGold() >= candy.price)
        {
            if (player.isInventoryFull())
            {
                if (player.swapMenu(candy) == true)
                {
                    board.removeCandyinStore(candy_store_idx, candy.name);
                    player.setGold(player.getGold() - candy.price);
                    return;
                }
                else
                {
                    return;
                }
            }
            else
            {
                player.addCandy(candy);
                board.removeCandyinStore(candy_store_idx, candy.name);
                player.setGold(player.getGold() - candy.price);
                cout << "Here is your updated candy inventory:" << endl;
                player.printInventory();
                return;
            }
        }
        else
        {
            cout << "You do not have enough gold to buy this candy. Since you can't read you can leave." << endl;
            return;
        }
    }
    else
    {
        cout << "You chose not to visit the candy store." << endl;
        return;
    }
}
// Asks if player wants to visit candy store and what they want to buy and edits appropriate inventories
bool isCalamity(Board board, int position)
{
    srand(time(0));
    if (!board.isTileSpecial(position))
    {
        int random = rand() % 5;
        if (random < 2)
        {
            return true;
        }
    }
    return false;
}
// Chance stuff 40% chance
// needs to be regular tile

// void winner(Player player){

// }
void calamity(Player &player)
{
    srand(time(0));
    cin.ignore(1000000, '\n');
    int random = rand() % 100;
    if (random < 30)
    {
        cout << "Oh no! Candy Bandits have swiped your gold coins!" << endl;
        int random = rand() % 10 + 1;
        player.setGold(player.getGold() - random);
        cout << "You lost " << random << " gold coins."
             << "and now have " << player.getGold() << " gold coins." << endl;
    }
    else if (random < 65)
    {
        cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
        cout << "This costs you a turn while trying to find your way back, you can recover by winning a game of rock paper scissors." << endl;
        if (playRockPaperScissors() == true)
        {
            cout << "You found your way out of the lolliop labyrinth!" << endl;
            return;
        }
        else
        {
            cout << "You lost the game of rock paper scissors and are still lost in the lollipop labyrinth." << endl;
            player.editTurns(-1);
            return;
        }
    }

    else if (random < 80)
    {
        cout << "Watch out! A candy avalanche has struck!" << endl;
        cout << "This costs you a turn and some stamina while trying to dig yourself out, you can recover by winning a game of rock paper scissors." << endl;
        if (playRockPaperScissors() == true)
        {
            cout << "You dug your way out of the candy avalanche" << endl;
            return;
        }
        else
        {
            cout << "You lost the game of rock paper scissors and are still engulfed by candy" << endl;
            int random2 = rand() % 6 + 5;
            cout << "You lost " << random2 << " stamina." << endl;
            player.setStamina(player.getStamina() - random2);
            player.editTurns(-1);
            return;
        }
    }
    else
    {
        cout << "Oops! You are stuck in a sticky taffy trap!" << endl;
        cout << "This immobilzes you for one turn but, you can recover by using a magic candy." << endl;
        Candy temp = player.findMagicinInventory();
        if (temp.name == "")
        {
            cout << "Sadly, you do not have a magic candy to use." << endl;
            player.editTurns(-1);
            return;
        }
        else
        {
            cout << "You have a magic candy to use." << endl;
            cout << "It is called " << temp.name << endl;
            cout << "Would you like to use it? (y/n)" << endl;
            char choice;
            cin >> choice;
            while (cin.fail() || (choice != 'y' && choice != 'n'))
            {
                cout << "Invalid selection!" << endl;
                cin.clear();
                cin.ignore(1000000, '\n');
                cin >> choice;
            }
            if (choice == 'y')
            {
                player.removeCandy(temp.name);
                return;
            }
            else
            {
                cout << "You chose not to use the magic candy. You are immobilized for a turn." << endl;
                player.editTurns(-1);
                return;
            }
        }
    }
}

void marshmallow(Board &board)
{
    srand(time(0));
    int random = rand() % 20;
    int move = 0;
    if (random == 13)
    {
        cout << "A Marshmallow hailstorm is occuring! Brace yourselves!" << endl;
        if (board.getPlayerPosition(0) < board.getPlayerPosition(1))
        {
            move = rand() % board.getPlayerPosition(0)+1;
        }
        else
        {
            move = rand() % board.getPlayerPosition(1)+1;
        }
        board.movePlayer(-move, 0);
        board.movePlayer(-move, 1);
        cout << "All players have been blown " << move << " spaces back!" << endl;
    }
}
void gummy(Player &player, Board board, int idx)
{
    int position = board.getPlayerPosition(idx);
    Gummy temp = board.getGummy(position);
    if (temp.dbl == true)
    {
        cout << "You have landed on a double gummy tile!" << endl;
    }
    else
    {
        cout << "You have landed on a single gummy tile!" << endl;
    }
    if (temp.dbl == true)
    {
        player.editTurns(-2);
    }
    else if (temp.dbl == false)
    {
        player.editTurns(-1);
    }
    board.removeGummy(position);
}
void special(Player &player, int idx, Board &board)
{
    int random = rand() % 4;
    Card card1 = drawCard();
    int random2;
    switch (random)
    {
    case 0:
        cout << "Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle." << endl;
        board.movePlayer(4, idx);
        break;
    case 1:
        cout << "Congrats! You get a chance to draw a card again." << endl;
        if (card1.twox == true)
        {
            cout << "You have drawn a double " << card1.color << " card!" << endl;
        }
        else
        {
            cout << "You have drawn a " << card1.color << " card!" << endl;
        }
        movePlayer(idx, card1, board);
        break;
    case 2:
        random2 = rand() % 6 + 5;
        cout << " Oops, You head back 4 tiles and lose " << random2 << " gold" << endl;
        player.setGold(player.getGold() - random2);
        player.displayStats();
        board.movePlayer(-4, idx);
        break;
    case 3:
        cout << "You landed on a Gingerbread House Tile" << endl;
        cout << "You are transported back to your previous position!" << endl;
        Candy temp = player.findImmunityinInventory();
        if (temp.name == "")
        {
            cout << "You did not have an immunity candy, so nothing was removed" << endl;
        }
        else
        {
            cout << "An immunity candy was lost on your journey." << endl;
        }

        player.removeCandy(temp.name);
        int old = board.getOldPlayerPosition(idx);
        board.setPlayerPosition(old, idx);
        break;
    }
}

void useCandy(Player players[], int idx, Board &board, vector<Riddle> &riddles)
{
    if (players[idx].getCandyAmount() == 0)
    {
        cout << "You have no candies to use!" << endl;
        return;
    }
    int otheridx;
    if (idx == 1)
    {
        otheridx = 0;
    }
    else
    {
        otheridx = 1;
    }
    cout << "Here is your list of candies:" << endl;
    players[idx].printInventory();
    cout << "Enter a candy you wish to use" << endl;
    string candy_name;
    getline(cin, candy_name);
    Candy temp = players[idx].findCandy(candy_name);
    while (cin.fail() || temp.name == "")
    {
        cout << "Invalid selection! Pick a candy from your inventory" << endl;
        cin.clear();
        getline(cin, candy_name);
        temp = players[idx].findCandy(candy_name);
    }
    if (temp.candy_type == "treasure")
    {
        cout << "You have used a treasure candy! Answer this riddle for a reward!" << endl;
        if (solveRiddle(riddles))
        {
            rewardTreasure(players[idx]);
        }
        players[idx].removeCandy(temp.name);
        cout << "You used " << temp.name << endl;
        return;
    }
    else if (temp.candy_type == "special")
    {
        if (temp.effect_type == "stamina")
        {
            players[idx].setStamina(players[idx].getStamina() + temp.effect_value);
            cout << "You successfully used " << temp.name << " candy. This has increased your" << temp.effect_value << " by " << temp.effect_type << " points." << endl;
            players[idx].removeCandy(temp.name);
            return;
        }
    }
    else if (temp.candy_type == "immunity")
    {
        cout << "You cannot use an immunity candy unless you are poisoned" << endl;
        useCandy(players, idx, board, riddles);
        return;
    }
    else if (temp.candy_type == "poison")
    {
        int poison = temp.effect_value;
        int level;
        if (poison == -10)
        {
            level = 1;
        }
        else if (poison == -15)
        {
            level = 2;
        }
        else
        {
            level = 3;
        }
        cout << "Do you want to use " << temp.name << " candy against your opponent?(y/n)" << endl;
        char choice;
        cin >> choice;
        while (cin.fail() || (choice != 'y' && choice != 'n'))
        {
            cout << "Invalid selection!" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            cin >> choice;
        }
        if (choice == 'y')
        {
            switch (level)
            {
            case 1:
                if (players[otheridx].findImmunity1inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity1inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity1inInventory().name);
                    return;
                }
                else if (players[otheridx].findImmunity2inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity2inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity2inInventory().name);
                    return;
                }
                else if (players[otheridx].findImmunity3inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity3inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity3inInventory().name);
                    return;
                }
                else
                {
                    cout << "Your opponent does not have an immunity candy to counteract your " << temp.name << " candy" << endl;
                    players[otheridx].setStamina(players[otheridx].getStamina() + temp.effect_value);
                    cout << "Your opponent's stamina suffered a " << temp.effect_value << " decrement" << endl;
                    players[idx].removeCandy(temp.name);
                    return;
                }
                break;
            case 2:
                if (players[otheridx].findImmunity2inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity2inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity2inInventory().name);
                    return;
                }
                else if (players[otheridx].findImmunity3inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity3inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity3inInventory().name);
                    return;
                }
                else
                {
                    cout << "Your opponent does not have an immunity candy to counteract your " << temp.name << " candy" << endl;
                    players[otheridx].setStamina(players[otheridx].getStamina() + temp.effect_value);
                    cout << "Your opponent's stamina suffered a " << temp.effect_value << " decrement" << endl;
                    players[idx].removeCandy(temp.name);
                    return;
                }
                break;
            case 3:
                if (players[otheridx].findImmunity3inInventory().name != "")
                {
                    cout << "You have used " << temp.name << " candy but your oppononent has " << players[otheridx].findImmunity3inInventory().name << " candy to protect against your poison candy." << endl;
                    players[idx].removeCandy(temp.name);
                    players[otheridx].removeCandy(players[otheridx].findImmunity3inInventory().name);
                    return;
                }
                else
                {
                    cout << "Your opponent does not have an immunity candy to counteract your " << temp.name << " candy" << endl;
                    players[otheridx].setStamina(players[otheridx].getStamina() + temp.effect_value);
                    cout << "Your opponent's stamina suffered a " << temp.effect_value << " decrement" << endl;
                    players[idx].removeCandy(temp.name);
                    return;
                }
                break;
            }
        }
        else
        {
            cout << "You chose not to use your poison candy" << endl;
            useCandy(players, idx, board, riddles);
            return;
        }
    }
    else if (temp.candy_type == "magical")
    {
        cout << "You have used " << temp.name << " and have gained " << temp.effect_value << " stamina!" << endl;
        players[idx].setStamina(players[idx].getStamina() + temp.effect_value);
        players[idx].removeCandy(temp.name);
        return;
    }
    else if (temp.candy_type == "gummy")
    {
        cout << "On which tile do you want to place your " << temp.name << " - gummy candy?" << endl;
        int gummypos;
        cin >> gummypos;
        while (cin.fail() || gummypos < 0 || gummypos > 83)
        {
            cout << "Invalid selection! Pick a tile on the board(1-83)" << endl;
            cin.clear();
            cin.ignore(1000000, '\n');
            cin >> gummypos;
        }
        cout << "You have successfully placed gummy candy on tile " << gummypos << ". Any player that lands on the gummy tile will be obstructed from advancing." << endl;
        gummypos--;
        players[idx].removeCandy(temp.name);
        board.addGummy(gummypos, temp.effect_value);
        return;
    }
}
// idx is the player who is using candy

bool mainMenu(Player players[], int playeridx, Board &board, vector<Riddle> &riddles)
{
    int choice;
    cout << "It's " << players[playeridx].getName() << " turn" << endl;
    cout << "Please select a menu option:" << endl;
    cout << "1. Draw a card" << endl;
    cout << "2. Use candy" << endl;
    cout << "3. Show player stats" << endl;
    cin >> choice;
    Card card;
    while (cin.fail() || (choice != 1 && choice != 2 && choice != 3))
    {
        cout << "Invalid selection!" << endl;
        cin.clear();
        cin.ignore(1000000, '\n');
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        board.setOldPlayerPosition(board.getPlayerPosition(playeridx), playeridx);
        card = drawCard();
        movePlayer(playeridx, card, board);
        return true;
        break;
    case 2:
        cin.ignore(1000000, '\n');
        useCandy(players, playeridx, board, riddles);
        cin.clear();
        return false;
        break;
    case 3:
        players[playeridx].displayStats();
        cout << endl;
        if (mainMenu(players, playeridx, board, riddles) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;
    }
    return false;
}
int main()
{
    // int candy_store_idx;
    Board board;
    vector<Candy> main = loadCandies("candy.txt");
    vector<Riddle> riddles = loadRiddles("riddles.txt");
    board.createCandystores(main);
    cout << "Welcome to Candyland!" << endl;
    cout << "This is a 2 player game." << endl;
    vector<Player> CHARACTERS = loadCharacters("characters.txt", main);
    Player player1 = choosePlayer(CHARACTERS);
    cout << endl;
    int initial = player1.getCandyAmount();
    candyStoreMenu(player1, board, 0);
    cout << endl;
    if(initial == player1.getCandyAmount()){
        cin.ignore(1000000, '\n');
    }
    Player player2 = choosePlayer(CHARACTERS);
    cout << endl;
    candyStoreMenu(player2, board, 0);
    cout << endl;
    Player players[2] = {player1, player2};

    // mainMenu(players, 1, board, riddles);
    bool running = true;
    bool ranoutofstam[2] = {false, false};
    while (running == true)
    {
        bool turn[2] = {true, true};
        if (players[1].getTurns() == players[0].getTurns())
        {
            players[1].setTurns(0);
            players[0].setTurns(0);
        }
        for (int i = 0; i < 2; i++)
        {
            srand(time(0));
            if (players[i].getTurns() < 0)
            {
                players[i].editTurns(1);
                turn[i] = false;
            }
            if (players[i].getTurns() == 0 && ranoutofstam[i] == true)
            {
                ranoutofstam[i] = false;
                players[i].setStamina(20);
            }
            if (players[i].getStamina() <= 0 && ranoutofstam[i] == false)
            {
                cout << players[i].getName() << " ,you have run out of stamina, you must wait two turns to recover" << endl;
                players[i].editTurns(-2);
                ranoutofstam[i] = true;
            }
            if (turn[i] == true && ranoutofstam[i] == false)
            {

                board.displayBoard();
                cout << endl;
                if (mainMenu(players, i, board, riddles) == true)
                {
                    board.displayBoard();
                    cout << endl;
                    int position = board.getPlayerPosition(i);
                    if (position >= 82)
                    {
                        cout << "You have reached the Candy Castle!" << endl;
                        cout << "You have won the game!" << endl;
                        cout << "Here are your final stats:" << endl;
                        cout << "Name: " << players[i].getName() << endl;
                        cout << "Character: " << players[i].getCharacter() << endl;
                        cout << "Stamina: " << players[i].getStamina() << endl;
                        cout << "Gold: " << players[i].getGold() << endl;
                        cout << "Here is your final inventory:" << endl;
                        players[i].printInventory();
                        ofstream of("winner.txt");
                        if (of.is_open())
                        {
                            of << "Name: " << players[i].getName() << endl;
                            of << "Character: " << players[i].getCharacter() << endl;
                            of << "Gold: " << players[i].getGold() << endl;
                            of << "Stamina: " << players[i].getStamina() << endl;
                            of << "Candies: " << endl;
                            vector<Candy> Candy = players[i].getInventory();
                            for (int j = 0; j < players[i].getCandyAmount(); j++)
                            {
                                of << Candy[j].name << endl;
                            }
                            of.close();
                        }
                        running = false;
                        break;
                    }
                    else
                    {
                        if (board.isPositionCandyStore(position) == true)
                        {
                            candyStoreMenu(players[i], board, position);
                        }
                        if (board.isTileSpecial(position) == true)
                        {
                            special(players[i], i, board);
                            position = board.getPlayerPosition(i);
                        }
                        else
                        {
                            if (isCalamity(board, position) == true)
                            {
                                calamity(players[i]);
                                position = board.getPlayerPosition(i);
                            }
                        }
                        if (board.isTileGummy(position) == true)
                        {
                            gummy(players[i], board, i);
                        }
                        if (board.isTileTreasure(position) == true)
                        {
                            cout << "You landed on a treasure tile!" << endl;
                            if (solveRiddle(riddles) == true)
                            {
                                rewardTreasure(players[i]);
                            }
                        }
                        if (board.rob(i) == true)
                        {
                            int otherindex;
                            if (i == 0)
                            {
                                otherindex = 1;
                            }
                            else
                            {
                                otherindex = 0;
                            }
                            cout << "You are getting robbed by " << players[otherindex].getName() << " !" << endl;
                            int random = rand() % 26 + 5;
                            Candy temp = players[i].findCandy("Robber's Rappel");
                            if (temp.name != "")
                            {
                                cout << "You have a Robber's Rappel candy to protect you from the robbery!" << endl;
                                players[i].removeCandy(temp.name);
                                board.movePlayer(-1, otherindex);
                            }
                            else
                            {
                                cout << "You do not have a Robber's Rappel candy to protect you from the robbery!" << endl;
                                cout << "You have lost " << random << " gold coins." << endl;
                                players[i].setGold(players[i].getGold() - random);
                                cout << "You now have " << players[i].getGold() << " gold coins." << endl;
                                players[otherindex].setGold(players[otherindex].getGold() + random);
                                cout << players[otherindex].getName() << " now has " << players[otherindex].getGold() << " gold coins." << endl;
                            }
                        }
                        marshmallow(board);
                    }
                }
            }
        }
        // useCandy(players, 1, board, riddles);

        // candyStoreMenu(player1, board, 0);
        // Make candies/inventories
        /*
        Candy one{"Frosty Fizz", "Boosts player's stamina by 10 units", "stamina", 10, "magical", 10};
        Candy two{"Toxic Taffy", "Decreases opponents stamina by 20 units(strong)", "stamina", -20, "poison", 25};
        Candy three{"Caramel Comet", "Protects against all poison candies", "other", 3, "immunity", 25};
        Candy four{"Swedish Fish", "Does nothing", "other", 5, "play fortnite", 23};
        Candy five{"Kelpish Fish", "Does something", "stamina", 23, "play fortnite", 32};
        Candy six{"Norwegian Fish", "Does everything", "other", 13, "play fortnite", 98};

        Candy oneInv[3] = {one, two, four};
        Candy twoInv[3] = {two, six, five};
        Candy threeInv[3] = {five, three, two};

        Candy playercandy[9] = {six, five, one, two, three, five, six, three, two};

        Player Player{"Lebron James", "Michelle Obama", 12, 12, playercandy, 9};

        (assert(Player.getName() == "Lebron James"));
        (assert(Player.getStamina() == 12));
        (assert(Player.getCharacter() == "Michelle Obama"));
        Player.printInventory();

        // Make all candy stores
        Candystore Store1{"Store1", oneInv, 3};
        Candystore Store2{"Store2", twoInv, 3};
        Candystore Store3{"Store3", threeInv, 3};
        Candystore candy_stores[] = {Store1, Store2, Store3};
        Candy temp = candy_stores[0].findCandy("Toxic Taffy");
        cout << "mm ethan" << endl;
        cout << temp.description << endl;
        cout << temp.name << endl;
        // Add the candy stores to baord
        board.addCandyStore(38);
        board.addCandyStore(58);
        board.addCandyStore(69);
        (assert(Store1.getName() == "Store1"));
        Store2.setName("Obama");
        (assert(Store2.getName() == "Obama"));

        for (int i = 0; i < board.getBoardSize(); i++)
        {
            board.setPlayerPosition(i, 0);
            if (board.isPositionCandyStore(i))
            {
                cout << endl;
                board.displayBoard();
                candy_store_idx = board.getCandyStoreIndex(i);
                candy_stores[candy_store_idx].displayCandy();
            }
        }
        */
    }
    return 0;
}