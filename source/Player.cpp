#include "player.h"

Player::Player() {
    cur_x = cur_y = 0;
    
    score = 0;
    max_bombs = 0;
    blast_pow = 0;
}

int Player::getX() {
    return cur_x;
}

int Player::getY() {
    return cur_y;
}