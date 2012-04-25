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

	AIPlayer();
	void randStart(int size);
	int randMove();
	void update(int x);
	void resetTimer();
};

#endif
