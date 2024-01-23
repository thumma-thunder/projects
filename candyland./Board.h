#ifndef BOARD_H
#define BOARD_H
#include "Candystore.h"
#include <iostream>
#include <vector>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Candy;





struct Tile
{
    string color;
    string tile_type;
    bool dbl;
};
struct Gummy{
    int position;
    bool dbl;
};

class Board
{
private:
    //Board tiles
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    //Candystore tiles
    const static int _MAX_CANDY_STORE = 4;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    Candystore candystores[_MAX_CANDY_STORE];
    int _player_position[2]; //[2] Array of players to allow two players to play

    int old_player_position[2];
    

    //Treasure Tiles
    const static int _MAX_TREASURE = 3;
    int _treasure_position[_MAX_TREASURE];
    int _treasure_count;

    const static int _MAX_SPECIAL = 15;   
    int _special_count;
    vector<Gummy> gummies;

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();

    bool setPlayerPosition(int, int); //add another int as input that is index (0 for player 1, 1 for player 2)

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition(int) const;
    int getCandyStoreIndex(int board_position);

    int getOldPlayerPosition(int);
    void setOldPlayerPosition(int, int);

    bool isTileSpecial(int);


    bool movePlayer(int tile_to_move_forward, int playerindex);

    bool addTreasure(int);
    int getTreasureCount() const;
    bool isTileTreasure(int);

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 
    void createCandystores(vector<Candy> candies);
    void removeCandyinStore(int, string);
    Candystore getCandystore(int idx);

    void addGummy(int, int); // postion, effect value to determine double
    Gummy getGummy(int); //returns gummy depending on position
    bool isTileGummy(int); //checks the vector of gummies and see if the position is in there matches
    int findGummyIndex(int);//helper function to find gummy index
    bool removeGummy(int); //removes gummy from vector

    bool castle(int playerindex); //checks if player is at the castle   

    bool rob(int playerindex); //checks if players share the same position and if they do, they can rob each other index is for player that just landed on tile
};

#endif