//
#include "AIPlayer.h"

AIPlayer::AIPlayer(){
	alive = 1;
	cur_x =0;
	cur_y =0;
	max_bombs =3;
	score=0;
	blast_pow=1;
	bombTimer = 3;
}

void AIPlayer::resetTimer(){
	bombTimer = 3;
}

int AIPlayer::randMove(){
	int rm;	//1 = UP; 2 = DOWN; 3 = RIGHT; 4 = LEFT
	rm = rand() % 4 + 1;
	return rm;
}

void AIPlayer::randStart(int size){
	int rm;
	rm = rand() % size;
	cur_x = rm;
	rm = rand() % size;
	cur_y = rm;
}

void AIPlayer::update(int x){
	if(x == 1)
		cur_x--;
	else if(x == 2)
		cur_x++;
	else if(x == 3)
		cur_y++;
	else
		cur_y--;
}
