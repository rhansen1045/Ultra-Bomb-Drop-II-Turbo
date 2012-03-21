#include <stdio.h>

#include "Level.h"

int main() {
    
    Level* lvl = new Level();
    
    lvl->generate();
    
    
    for(int i = 0; i < LEVEL_ROW; ++i) {
        for(int j = 0; j < LEVEL_COL; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND) {
                printf("o");
            } else if(tile == SOLID) {
                printf("*");
            } else if(tile == BREAK) {
                printf("B");
            }
        }
        printf("\n");
    }
    
}