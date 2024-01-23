#include "Player.h"
#include <iostream>
#include <vector>

using namespace std;

Player::Player()
{
    _name = "";
    _character = "";
    _stamina = 0;
    _gold = 0.00;
    _candy_amount = 0;
    _turns=0;
};

Player::Player(string name, string character, int stam, double gold, Candy candy_array[], const int CANDY_ARR_SIZE)
{
    _name = name;
    _character = character;
    _stamina = stam;
    _gold = gold;
    _candy_amount = 0;
    _turns=0;
    for (int i = 0; i < CANDY_ARR_SIZE && _candy_amount < _MAX_CANDY_AMOUNT; i++)
    {
        if (candy_array[i].name != "")
        {
            _inventory[_candy_amount++] = candy_array[i];
        }
    }
};

string Player::getName(){
    return _name;
}
void Player::setName(string name){
    _name=name;
}
string Player::getCharacter(){
    return _character;
}
void Player::setCharacter(string character){
    _character=character;
}
int Player::getCandyAmount()
{
    return _candy_amount;
}
void Player::setCandyAmount(int candy)
{
    _candy_amount = candy;
}


void Player::setStamina(int stam)
{
    if(stam>100){
        stam=100;
    }
    else if(stam<0){
        stam=0;
    }
    _stamina = stam;
}
int Player::getStamina()
{
    return _stamina;
}
void Player::setGold(double gold)
{
    if(gold>100.0){
        gold=100.0;
    }
    else if(gold<0){
        gold=0;
    }
    _gold = gold;
}
double Player::getGold()
{
    return _gold;
}

void Player::printInventory()
{
    string name;
    for (int i = 1; i < _MAX_CANDY_AMOUNT+1; i++)
    {
        name = _inventory[i-1].name;
        if (i % 3 == 0)
        {
            if (name == "")
            {
                name = "Empty";
            }

            cout << "[" << name << "]  " << endl;
        }
        else
        {
            if (name == "")
            {
                name = "Empty";
            }
            cout << "[" << name << "]  ";
        }
    }
    return;
}

Candy Player::findCandy(string candy_name)
{
    string test = "";
    for (unsigned int j = 0; j < candy_name.length(); j++)
    {
        candy_name[j] = tolower(candy_name[j]);
    }
    for (int i = 0; i < _candy_amount; i++)
    {
        test = _inventory[i].name;
        for (unsigned int j = 0; j < _inventory[i].name.length(); j++)
        {
            test[j] = tolower(_inventory[i].name[j]);
        }
        if (test == candy_name)
        {
            return _inventory[i];
        }
    }
    Candy T;
    return T;
}

bool Player::addCandy(Candy C)
{
    if (_candy_amount < _MAX_CANDY_AMOUNT)
    {
        _inventory[_candy_amount++] = C;
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::removeCandy(string candy_name)
{
    string test;
    Candy temp = findCandy(candy_name);
    for (unsigned int j = 0; j < candy_name.length(); j++)
    {
        candy_name[j] = tolower(candy_name[j]);
    }
    for (int i = 0; i < _candy_amount; i++)
    {
        test = _inventory[i].name;
        for (unsigned int j = 0; j < _inventory[i].name.length(); j++)
        {
            test[j] = tolower(_inventory[i].name[j]);
        }

        if (test == candy_name)
        {
            for (int j = i; j < _candy_amount - 1; j++)
            {
                _inventory[j] = _inventory[j + 1];
            }
            Candy T;
            _inventory[_candy_amount - 1] = T;
            _candy_amount--;
            return true;
        }
    }
    return false;
}


int Player::findCandyIndex(Candy candy){
    string name = candy.name;
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].name==name){
                return i;
        }
    }
   return -1;
}

void Player:: swapCandy(Candy gain, Candy lose){
    int idx =findCandyIndex(lose);
    _inventory[idx]=gain;

}

bool Player:: swapMenu(Candy gain){
                cout << "You do not have sufficient place in the candy inventory. Would you like to substitute your candy with any existing candy?(y/n)" << endl;
                char choice;
                while (cin.fail() || (choice != 'y' && choice != 'n'))
                {
                    cout << "Invalid selection!" << endl;
                    cin.clear();
                    cin.ignore(1000000, '\n');
                    cin >> choice;
                }
                if (choice == 'y')
                {
                    cout << "Which candy would you like to substitute?" << endl;
                    string sub_name;
                    getline(cin, sub_name);
                    while (cin.fail())
                    {
                        cout << "Invalid selection!" << endl;
                        cin.clear();
                        cin.ignore(1000000, '\n');
                        getline(cin, sub_name);
                    }
                    Candy sub_candy = findCandy(sub_name);
                    while (sub_candy.name == "")
                    {
                        cout << "Invalid selection! Choose a candy in your inventory" << endl;
                        cout << "Here is your inventory:" << endl;
                        printInventory();
                        getline(cin, sub_name);

                        while (cin.fail())
                        {
                            cout << "Invalid selection!" << endl;
                            cin.clear();
                            cin.ignore(1000000, '\n');
                            getline(cin, sub_name);
                        }
                        sub_candy = findCandy(sub_name);
                    }
                    swapCandy(gain, sub_candy);
                    cout << "Here is your updated candy inventory:" << endl;
                    printInventory();
                    return true;
                }
                else
                {
                    cout << "You chose not to substitute a candy." << endl;
                    return false;
                }
            }

    
bool Player::isInventoryFull(){
    if(_candy_amount==_MAX_CANDY_AMOUNT){
        return true;
    }
    else{
        return false;
    }
}

void Player:: displayStats(){
    cout<<"Player name: "<<_name<<endl;
    cout<<"Character: "<<_character<<endl;
    cout<<"Stamina: "<<_stamina<<endl;
    cout<<"Gold: "<<_gold<<endl;
    cout<<"Candies:"<<endl;
    printInventory();
    cout<<endl;
    return;
}

void Player::displayCharStats(){
    cout<<"Name: "<<_character<<endl;
    cout<<"Stamina: "<<_stamina<<endl;
    cout<<"Gold: "<<_gold<<endl;
    cout<<"Candies:"<<endl;
    printInventory();
    cout<<endl;
    return;
}

Candy Player::findMagicinInventory(){
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].candy_type=="magical"){
            return _inventory[i];
        }
    }
    Candy T;
    return T;
}

Candy Player::findImmunityinInventory(){
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].candy_type=="immunity"){
            return _inventory[i];
        }
    }
    Candy T;
    return T;
}

int Player::getTurns(){
    return _turns;
}

void Player::setTurns(int turns){
    _turns=turns;
}

void Player::editTurns(int turns){
    _turns+=turns;
    return;
}

Candy Player::findImmunity1inInventory(){
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].candy_type=="immunity"){
            if(_inventory[i].effect_value==1){
                return _inventory[i];
            }
        }
    }
    Candy T;
    return T;
}

Candy Player::findImmunity2inInventory(){
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].candy_type=="immunity"){
            if(_inventory[i].effect_value==2){
                return _inventory[i];
            }
        }
    }
    Candy T;
    return T;
}

Candy Player::findImmunity3inInventory(){
    for(int i=0;i<_candy_amount;i++){
        if(_inventory[i].candy_type=="immunity"){
            if(_inventory[i].effect_value==3){
                return _inventory[i];
            }
        }
    }
    Candy T;
    return T;
}

vector<Candy> Player::getInventory(){
    vector<Candy> candy;
    for(int i=0;i<_candy_amount;i++){
        candy.push_back(_inventory[i]);
    }
    return candy;
}