#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

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

class LocalPlayer : public Player {
public:
    LocalPlayer();
	void randStart(int size);
    void update(int x);
};

#endif
