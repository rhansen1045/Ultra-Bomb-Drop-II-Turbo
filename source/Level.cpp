#include "Level.h"
#include <stdlib.h>
#include <time.h>
Level::Level() {
    
    srand(time(NULL));
    generate();
    
}

void Level::generate() {
    //blank for now
    for(int i = 0; i < LEVEL_COL; ++i) {
        for(int j = 0; j < LEVEL_ROW; ++j) {
            if(j == 0) {
                board_data[0][i] = SOLID;
            } else if (j == LEVEL_COL-1) {
                board_data[LEVEL_COL-1][i] = SOLID;
            } else {
                if(i == 0) {
                    board_data[j][0] = SOLID;
                } else if (i == LEVEL_ROW-1) {
                    board_data[j][LEVEL_ROW-1] = SOLID;
                } else {
                    //
                    if((j%2) != 0) {
                        board_data[j][i] = GROUND;
                    } else if((i % 2) == 0) {
                        board_data[j][i] = SOLID;
                    } else {
                        board_data[j][i] = GROUND;
                    }
                    
                }
            }
        }
    }
    
    for(int i = 0; i < DESTROY_BLOCKS; ++i) {
        int x = rand()%LEVEL_COL;
        int y = rand()%LEVEL_ROW;
        
        if(board_data[y][x] == GROUND) {
            board_data[y][x] = BREAK;
        } else {
            i--;
        }
    }
    
}

void Level::add_player(Player* player) {
    players.push_back(player);
}

//void Level::set_local(LocalPlayer* player) {
//    local = player;
//}

void Level::update(int x, int y, Tile t) { //This should be in the main game loop with SDL
    //Go through all objects and call update
	board_data[x][y] = t;
}

void Level::printBoard(){
	for(int x=0; x<LEVEL_ROW; x++){
		for(int y=0; y<LEVEL_COL; y++){
			Tile t = get_tile(y, x);
			if(t == GROUND)
				printf(" ");
			else if(t == SOLID)
				printf("I");
			else if(t == BREAK)
				printf("B");
		}
		printf("\n");
	}
}

Tile Level::get_tile(int x, int y) {
    return board_data[x][y];
}
