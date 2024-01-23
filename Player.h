#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"

#include <iostream>
#include <string>

using namespace std;

struct Candy; /*
{
    string name;
    string description;
    string effect_type;
    int effect_value;
    string candy_type;
    double price;
};

*/
class Player
{
    private:
        const static int _MAX_CANDY_AMOUNT=9;
        string _name;
        string _character;
        int _stamina;
        double _gold;
        Candy _inventory[_MAX_CANDY_AMOUNT];
        int	_candy_amount;
        const static int _MAX_STAMINA=100;
        double _MAX_GOLD=100;
        int _turns;

    public:
        Player();
        Player(string, string, int stam,double gold,Candy candy_array[],const int CANDY_ARR_SIZE);
        string getName();
        void setName(string);
        string getCharacter();
        void setCharacter(string);
        int getCandyAmount();
        const int getMaxAmount();
        void setCandyAmount(int);
        void setStamina(int);
        int getStamina();
        void setGold(double);
        double getGold();
        void setEffect(string);
        string getEffect();
        void printInventory();
        Candy findCandy(string);
        bool addCandy(Candy);
        bool removeCandy(string candy_name);
        void swapCandy(Candy, Candy);
        bool swapMenu(Candy);
        int findCandyIndex(Candy);

        bool isInventoryFull();
        void displayStats();
        void displayCharStats();
        Candy findMagicinInventory();
        Candy findImmunityinInventory();
        vector<Candy> getInventory();
        Candy findImmunity1inInventory();
        Candy findImmunity2inInventory();
        Candy findImmunity3inInventory();

        //For poison handling

        int getTurns();
        void editTurns(int);
        void setTurns(int);

};

#endif
