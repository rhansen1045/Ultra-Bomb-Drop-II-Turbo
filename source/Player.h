#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Score.h"

using namespace std;

class Player {
    
    //Game specific stuff
    
public:
    Player();
    int cur_x;
    int cur_y;
    string name;
    int alive;
    int score;
    Score myScore;
    int bombTimer;
    int max_bombs;
    int blast_pow;
   // virtual ~Player() {
  //  }
    
    int getX();
    int getY();
    
   // virtual void update() {   
   // }
    
};

#endif
