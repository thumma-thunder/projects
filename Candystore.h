#ifndef CANDYSTORE_H
#define CANDYSTORE_H
#include <iostream>
#include <vector>
using namespace std;

struct Candy
{ 
    string name;
    string description;
    string effect_type;
    int effect_value;
    string candy_type;
    double price;
};
class Candystore{
    private:
        const static int _MAX_CANDIES=3;
        string _storeName;
        Candy _storeStock[_MAX_CANDIES];
        int _candy_count=0;


    public:
        Candystore();
        Candystore(string,Candy[],const int);
        string getName();
        int getCandyCount();
        void setName(string);
        void addCandy(Candy);
        bool removeCandy(string);
        Candy findCandy(string);
        void displayCandy();
        Candy findCandy();
};


#endif