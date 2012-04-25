#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(){
	alive = 1;
	cur_x = 0;
	cur_y = 0;
	max_bombs = 3;
	score = 0;
	blast_pow = 1;
	bombTimer = 3;
}

void LocalPlayer::randStart(int size){
	int rm;
	rm = rand() % size;
	cur_x = rm;
	rm = rand() % size;
	cur_y = rm;
}

void LocalPlayer::update(int x) {
	if(x==1)
		cur_x--;
	else if(x==2)
		cur_x++;
	else if(x==3)
		cur_y++;
	else
		cur_y--;
}
