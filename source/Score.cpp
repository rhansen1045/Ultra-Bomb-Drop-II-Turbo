#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "Highscore.h"
#include "Score.h"

Score::Score(){
	myScore = 0;
}

void Score::score_lastAlive(){
	myScore += 50;
}

void Score::score_kill(){
	myScore += 100;
}

void Score::score_3Alive(){
	myScore += 20;
}
void Score::score_2Alive(){
	myScore += 10;
}

void Score::score_inc(int x){
	myScore += x;
}

int Score::getScore(){
	return myScore;
}
