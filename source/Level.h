#ifndef LEVEL_H
#define LEVEL_H

#include "LocalPlayer.h"
#include "AIPlayer.h"

#include <vector>

using namespace std;

#define LEVEL_COL 11
#define LEVEL_ROW 11

#define DESTROY_BLOCKS 20

typedef enum {
    GROUND,
    SOLID,
    BREAK,
    AI,
    LOCAL,
    BOMB
} Tile;

class Level {
  
    Tile board_data[LEVEL_ROW][LEVEL_COL];
    
    
   // LocalPlayer* local;
    vector<Player*> players;
    
public:
    Level(); //Constructor to generate a random level
    
    void add_player(Player* player);
  //  void set_local(LocalPlayer* player);
    
    void generate(); //Generates a random level
    
    Tile get_tile(int x, int y);
    void printBoard();
    
    void update(int x, int y, Tile t);
};

#endif
