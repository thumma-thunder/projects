#include "Candystore.h"
#include <fstream>
#include <sstream>


Candystore::Candystore()
{
    _storeName = "";
    Candy _storeStock[_MAX_CANDIES];
};

Candystore::Candystore(string name, Candy _stock[], const int CANDY_ARR_SIZE){
    _storeName=name;
    _candy_count=0;
    for(int i=0;i<CANDY_ARR_SIZE&&_candy_count<_MAX_CANDIES;i++){
        if(_stock[i].name!=""){        
            _storeStock[_candy_count++] = _stock[i];
        }
    }
};

string Candystore::getName(){
    return _storeName;
}
void Candystore::setName(string name){
    _storeName=name;
}
//void Candystore::addCandy(Candy candy){}
    //Same as player class
    //Might not need
bool Candystore::removeCandy(string candy_name){
     string test;
    Candy temp = findCandy(candy_name);
    for (unsigned int j = 0; j < candy_name.length(); j++)
    {
        candy_name[j] = tolower(candy_name[j]);
    }
    for (int i = 0; i < _candy_count; i++)
    {
        test = _storeStock[i].name;
        for (unsigned int j = 0; j < _storeStock[i].name.length(); j++)
        {
            test[j] = tolower(_storeStock[i].name[j]);
        }

        if (test == candy_name)
        {
            for (int j = i; j < _candy_count - 1; j++)
            {
                _storeStock[j] = _storeStock[j + 1];
            }
            Candy T;
            _storeStock[_candy_count - 1] = T;
            _candy_count--;
            return true;
        }
    }
    return false;
}
   

Candy Candystore::findCandy(string candy_name){
    string test = "";
    for (unsigned int j = 0; j < candy_name.length(); j++)
    {
        candy_name[j] = tolower(candy_name[j]);
    }
    for (int i = 0; i < _candy_count; i++)
    {
        test = _storeStock[i].name;
        for (unsigned int j = 0; j < _storeStock[i].name.length(); j++)
        {
            test[j] = tolower(_storeStock[i].name[j]);
        }
        if (test == candy_name)
        {
            return _storeStock[i];
        }
    }
    Candy T;
    return T;
}
    //Same as player class

void Candystore::displayCandy(){
 string name;
    cout << "Here is a list of candies in the candy store:" << endl;
    for (int i = 0; i < _candy_count; i++){
        cout << "Name: " << _storeStock[i].name << endl
        << "Description: "<< _storeStock[i].description << endl
        << "Effect: "<< _storeStock[i].effect_type << endl
        << "Effect value: "<< _storeStock[i].effect_value << endl
        << "Candy type: "<< _storeStock[i].candy_type << endl
        << "Price: "<< _storeStock[i].price << endl;
        if(i!=_MAX_CANDIES-1){
            cout << "----------------------------------" << endl;
        }
    }
    return;
}

int Candystore::getCandyCount(){
    return _candy_count;
}