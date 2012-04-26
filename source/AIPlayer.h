#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "Score.h"
#include "Player.h"
#include "Level.h"

using namespace std;

class AIPlayer : public Player {
public:
	int latestMove;	//value to determine proper graphic to use
				//1=up, 2=down, 3=right, 4=left

	AIPlayer();
	void randStart(int size);
	int randMove();
	void update(int x);
	void resetTimer();
};

#endif
