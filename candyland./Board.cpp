#include "Board.h"
#include <cstdlib>
#include <ctime>
Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    srand(time(0));
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        int randspecial = rand() % 4;
        if (randspecial == 3&&_special_count<_MAX_SPECIAL)
        {
            new_tile = {current_color, "special tile"};
            _special_count++;
        }
        else
        { // Add probability for 25% chance of being a special tile
            new_tile = {current_color, "regular tile"};
        }
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    _treasure_count = 0;
    for (int i = 0; i < _MAX_TREASURE; i++)
    {
        _treasure_position[i] = -1;
    }
    addCandyStore(0);
    for (int i = 27; i < _BOARD_SIZE - 1||_candy_store_count<_MAX_CANDY_STORE; i = i+ 27)
    {
        int randomstore = rand() % 27;
        int tilehelp;
        if (i == 27)
        {
            tilehelp = 0;
            randomstore++; //prevents
        }
        else if (i == 54)
        {
            tilehelp = 1;
            randomstore+=27;
        }
        else
        {
            tilehelp = 2;
            randomstore+=54;
        }
        while (randomstore % 3 != tilehelp)
        {
            if (randomstore > i - 4)
            {
                randomstore--;
            }
            else
            {
                randomstore++;
            }
        }
        addCandyStore(randomstore);
    }

    // Add candy stores to random positions by using srand random number and using addCandyStore
    // Update their positions
    for (int i = 0; i < _MAX_TREASURE; i++)
    {
        int randomtreasure = rand() % _BOARD_SIZE;
        if (!isTileTreasure(randomtreasure))
        {
            addTreasure(randomtreasure);
        }
    }
    // Add treasure tiles to random positions buy getting random number and using addTreasure
    // Update their treasure positions

    _player_position[0] = 0;
    _player_position[1] = 0;
    old_player_position[0]=0;
    old_player_position[1]=0;
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    if (position == _player_position[0] || position == _player_position[1]) // add another if for the second index
    {
        if (position == _player_position[0])
            cout << "1";
        else
            cout << "2";
    }
    else
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position, int playidx) // add input for which player
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position[playidx] = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition(int playidx) const // add input for which player
{
    return _player_position[playidx];
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count++] = position;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward, int playidx) // add second input for which player
{
    int new_player_position = tile_to_move_forward + _player_position[playidx]; // add implementation for two players
    if (new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        if (new_player_position < 0)
        {
            new_player_position = 0;
        }
        else if (new_player_position == _BOARD_SIZE-1)
        {
            new_player_position = _BOARD_SIZE - 1;
            _player_position[playidx] = new_player_position;
        }
        return false;
    }
    _player_position[playidx] = new_player_position;
    return true;
}
int Board::getCandyStoreIndex(int board_position)
{

    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return i;
        }
    }
    return -1;
}

bool Board::isTileTreasure(int position)
{
    for (int i = 0; i < _MAX_TREASURE; i++)
    {
        if (position == _treasure_position[i])
        {
            return true;
        }
    }
    return false;
}

bool Board::isTileSpecial(int position)
{
    for(int i=0;i<_MAX_SPECIAL;i++){
        if(_tiles[position].tile_type=="special tile"){
            return true;
        }
    }
    return false;
}

bool Board::addTreasure(int position){
     if (_treasure_count >= _MAX_TREASURE)
    {
        return false;
    }
    _treasure_position[_treasure_count++] = position;
    return true;
} // Add a treasure to the board (same as candy store)

int Board::getTreasureCount() const
{
    return _treasure_count;
}

void Board::createCandystores(vector<Candy> candies){ // complicated
    srand(time(0));
    vector<Candy> magical;
    vector<Candy> immunity;
    vector<Candy> poison;
    vector<Candy> gummy;


    for(unsigned int i=0;i<candies.size();i++){
        if(candies.at(i).candy_type=="magical"){
            magical.push_back(candies.at(i));
        }
        else if(candies.at(i).candy_type=="immunity"){
            immunity.push_back(candies.at(i));
        }else if(candies.at(i).candy_type=="poison"){
            poison.push_back(candies.at(i));
        }else if(candies.at(i).candy_type=="gummy"){
            gummy.push_back(candies.at(i));
        }
    }
    for(int i=0;i<_MAX_CANDY_STORE;i++){
        vector<string> types = {"magical","immunity","poison","gummy"};
        Candy candy[3]; 
        //creating array to create candy store CHANGE ^ and bottom if max candystore inventory is changed
        for(int r=0;r<3;r++){
            int random = rand()% types.size();
            if(types.at(random)=="magical"){
                int random1 = rand()% magical.size();
                candy[r]=magical.at(random1);
                for(unsigned int k=0;k<types.size();k++){
                    if(types.at(k)=="magical"){
                        string temp = types.at(k);
                        for (unsigned int j = k; j < types.size()-1; j++)
                        {
                            types.at(j) = types.at(j + 1);
                        }
                        types.at(types.size()-1)=temp;
                        types.pop_back();   
                    }
                }
            }
            else if(types.at(random)=="immunity"){
                int random1 = rand()% immunity.size();
                candy[r]=immunity.at(random1);

                for(unsigned int k=0;k<types.size();k++){
                    if(types.at(k)=="immunity"){
                        string temp = types.at(k);
                        for (unsigned int j = k; j < types.size()-1; j++)
                        {
                            types.at(j) = types.at(j + 1);
                        }
                        types.at(types.size()-1)=temp;
                        types.pop_back();   
                    }
                }
            }
            else if(types.at(random)=="poison"){
                int random1 = rand()% poison.size();
                candy[r]=poison.at(random1);

                for(unsigned int k=0;k<types.size();k++){
                    if(types.at(k)=="poison"){
                        string temp = types.at(k);
                        for (unsigned int j = k; j < types.size()-1; j++)
                        {
                            types.at(j) = types.at(j + 1);
                        }
                        types.at(types.size()-1)=temp;
                        types.pop_back();   
                    }
                }
            }
            else if(types.at(random)=="gummy"){
                int random1 = rand()% gummy.size();
                candy[r]=gummy.at(random1);

                for(unsigned int k=0;k<types.size();k++){
                    if(types.at(k)=="gummy"){
                        string temp = types.at(k);
                        for (unsigned int j = k; j < types.size()-1; j++)
                        {
                            types.at(j) = types.at(j + 1);
                        }
                        types.at(types.size()-1)=temp;
                        types.pop_back();   
                    }
                }
            }
            
        }

        const int candy_size = 3;
        Candystore LEBRON{"Candy Store",candy,candy_size};
        candystores[i]=LEBRON;
    }
}


Candystore Board::getCandystore(int idx){


    return candystores[idx];

}

void Board::removeCandyinStore(int idx, string candy_name){
    candystores[idx].removeCandy(candy_name);
}

void Board::setOldPlayerPosition(int position, int playidx){
    old_player_position[playidx]=position;
}

int Board::getOldPlayerPosition(int playidx){
    return old_player_position[playidx];
}

void Board::addGummy(int position, int effect_value){
    if(effect_value==1){
        Gummy gummy{position,false};
        gummies.push_back(gummy);
    }else if(effect_value==2){
        Gummy gummy{position,true};
        gummies.push_back(gummy);
    }
    

}

Gummy Board::getGummy(int position){
    for(unsigned int i=0;i<gummies.size();i++){
        if(gummies.at(i).position==position){
            return gummies.at(i);
        }
    }
    Gummy gummy{-1,false};
    return gummy;
}

int Board::findGummyIndex(int position){
    for(unsigned int i=0;i<gummies.size();i++){
        if(gummies.at(i).position==position){
            return i;
        }
    }
    return -1;
}

bool Board::isTileGummy(int position){
    for(unsigned int i=0;i<gummies.size();i++){
        if(gummies.at(i).position==position){
            return true;
        }
    }
    return false;
}

bool Board::removeGummy(int position){
    int idx = findGummyIndex(position);
    if(idx==-1){
        return false;
    }  
    Gummy temp =gummies.at(idx);
    for(unsigned int i=idx;i<gummies.size()-1;i++){
        gummies.at(i)=gummies.at(i+1);
    }
    gummies.at(gummies.size()-1)=temp;
    gummies.pop_back();
    return true;
}


bool Board::castle(int playidx){
    if(_player_position[playidx]==_BOARD_SIZE-1){
        return true;
    }
    return false;
}

bool Board::rob(int playidx){
    int otheridx;
    if(playidx==0){
        otheridx=1;
    }
    else{
        otheridx=0;
    }
    if(_player_position[playidx]==_player_position[otheridx]&&_player_position[playidx]!=0){
        return true;
    }
    return false;
}