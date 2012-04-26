#include "Game.h"

Game::Game(){
	gameBoard.generate();
	srand(time(NULL));
	randAIStart(11);
}

void Game::setBombRadius(int x){
	cout << "Bomb Radius set to: " << x << endl << endl;
	c1.blast_pow = x;
	c2.blast_pow = x;
	c3.blast_pow = x;
	p1.blast_pow = x;
}

void Game::setLocalName(string s){
	p1.name = s;
}

//place all 3 AIs and user player in random locations at start of the game
void Game::randAIStart(int n){
	int c = 0;
	c1.randStart(n);
	c = checkMove(c1,1) + checkMove(c1,2) + checkMove(c1,3) + checkMove(c1,4);
	while(c < 2 || gameBoard.get_tile(c1.cur_x, c1.cur_y) == BREAK || gameBoard.get_tile(c1.cur_x, c1.cur_y) == SOLID){
		c=0;
		c1.randStart(n);
		c= checkMove(c1,1) + checkMove(c1,2) + checkMove(c1,3) + checkMove(c1,4);
	}
	c2.randStart(n);
	c = checkMove(c2,1) + checkMove(c2,2) + checkMove(c2,3) + checkMove(c2,4);
	while(c < 2 || gameBoard.get_tile(c2.cur_x, c2.cur_y) == BREAK || gameBoard.get_tile(c2.cur_x, c2.cur_y) == SOLID || (c1.cur_x == c2.cur_x && c1.cur_y == c2.cur_y)){
		c=0;
		c2.randStart(n);
		c= checkMove(c2,1) + checkMove(c2,2) + checkMove(c2,3) + checkMove(c2,4);
	}
	c3.randStart(n);
	c = checkMove(c3,1) + checkMove(c3,2) + checkMove(c3,3) + checkMove(c3,4);
	while(c < 2  || gameBoard.get_tile(c3.cur_x, c3.cur_y) == BREAK || gameBoard.get_tile(c3.cur_x, c3.cur_y) == SOLID || (c1.cur_x == c3.cur_x && c1.cur_y == c3.cur_y) || (c2.cur_x == c3.cur_x && c2.cur_y == c3.cur_y)){
		c=0;
		c3.randStart(n);
		c= checkMove(c3,1) + checkMove(c3,2) + checkMove(c3,3) + checkMove(c3,4);
	}
	p1.randStart(n);
	c = checkMove(p1,1) + checkMove(p1,2) + checkMove(p1,3) + checkMove(p1,4);
	while(c < 2  || gameBoard.get_tile(p1.cur_x, p1.cur_y) == BREAK || gameBoard.get_tile(p1.cur_x, p1.cur_y) == SOLID || (c1.cur_x == p1.cur_x && c1.cur_y == p1.cur_y) || (c2.cur_x == p1.cur_x && c2.cur_y == p1.cur_y) || (c3.cur_x == p1.cur_x && c3.cur_y == p1.cur_y)){
		c=0;
		p1.randStart(n);
		c= checkMove(p1,1) + checkMove(p1,2) + checkMove(p1,3) + checkMove(p1,4);
	}
	c1.name = "c1";
	c2.name = "c2";
	c3.name = "c3";
	updateScores(0);
}

//if bomb is present in this position (x,y,) then return 1
//else return 0
int Game::checkforBombs(int x, int y){
	for(int z=0; z<bombs.size(); z++){
		if(bombs[z].loc_x == x && bombs[z].loc_y == y)
			return 1;
	}
	return 0;
}


// *********actual game function *****************
// **********loops continuously until there is only one player left alive
//********************************
void Game::singlePlayer(){
	int ch;
	string move;
	int pmove;
	int turns = 0;	//after 30 turns, give all players one more bomb
	while(true){
		printBoard();
		bombDec();			//decrease all bombs timers by 1
		if(p1.alive == 1){
		cout << "Move: ";		//input for user move
		cin >> move;
		while(move != "1" && move != "2" && move != "3" && move != "4" && move != "5"){
			cout << "Invalid Move - Choose 1 for up, 2 for down, 3 for right, 4 for left, 5 for drop bomb" << endl;
			cout << "Move: ";
			cin >> move;
		}
		istringstream( move ) >> pmove;
		if(pmove == 5 && p1.max_bombs > 0 && checkforBombs(p1.cur_x, p1.cur_y) == 0){		//set bomb if user's move = 5
			setBomb(p1.name, p1.blast_pow, p1.cur_x, p1.cur_y);
			p1.max_bombs--;
		}
		else if(checkMove(p1,pmove) == 1){
			p1.update(pmove);			//update player's position
		} }

		else{			//if user is dead, press enter to continue game
		ch = cin.get();
		printf("%c :\n", ch, int(ch));
		}

		//get moves from AI players
		int x;
		int c = checkMove(c1,1) + checkMove(c1,2) + checkMove(c1,3) + checkMove(c1,4);
		if(c1.alive == 1 && c !=0){		//c = 0, AI can't move (is blocked)
		//Random move for AI player 1
		x = c1.randMove();
		while(checkMove(c1, x) == 0){
			x = c1.randMove();
		}
		c1.update(x);		//update 1st AI position
		c1.latestMove = x;
		if(c1.max_bombs > 0 && x == 1 && checkforBombs(c1.cur_x, c1.cur_y) == 0){
			setBomb(c1.name, c1.blast_pow, c1.cur_x, c1.cur_y);
			c1.max_bombs--;}}


		c = checkMove(c2,1) + checkMove(c2,2) + checkMove(c2,3) + checkMove(c2,4);
		if(c2.alive == 1 && c != 0){
		//Random move for AI player 2
		x = c2.randMove();
		while(checkMove(c2, x) == 0){
			x = c2.randMove();}
		c2.update(x);		//update 2nd AI position
		c2.latestMove = x;
		if(c2.max_bombs > 0 && x == 1 && checkforBombs(c2.cur_x, c2.cur_y) == 0){
			setBomb(c2.name, c2.blast_pow, c2.cur_x, c2.cur_y);
			c2.max_bombs--;}}


		c = checkMove(c3,1) + checkMove(c3,2) + checkMove(c3,3) + checkMove(c3,4);
		if(c3.alive == 1 && c != 0){
		x = c3.randMove();			//Random AI 3 move
		while(checkMove(c3, x) == 0){
			x = c3.randMove();}
		c3.update(x);			//update 3rd AI player's position
		c3.latestMove = x;
		if(c3.max_bombs > 0 && x == 1 && checkforBombs(c3.cur_x, c3.cur_y) == 0){
			setBomb(c3.name, c3.blast_pow, c3.cur_x, c3.cur_y);
			c3.max_bombs--;}}
		turns++;
		if((turns % 3) == 0)
			updateScores(1);		//add 1 to score of all players who are alive
		if(turns == 30){		//give all players extra bomb after 30 turns
			c1.max_bombs++;	//avoids infinite game
			c2.max_bombs++;
			c3.max_bombs++;
			turns = 0;
		}
	}
}


//check if move is valid for LocalPlayer
int Game::checkMove(LocalPlayer c, int move){
	if(move == 1){		//CHECK MOVE UP
	//can't move through other players
		if((c2.cur_x == c.cur_x-1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c1.cur_x == c.cur_x-1 && c1.cur_y == c.cur_y && c1.alive == 1) || (c3.cur_x == c.cur_x-1 && c3.cur_y == c.cur_y && c3.alive == 1))
				return 0;
		if(gameBoard.get_tile(c.cur_x-1, c.cur_y) == SOLID)		//cant move through solid blocks
			return 0;
		else if(gameBoard.get_tile(c.cur_x-1, c.cur_y) == BREAK)	//cant move through breakable blocks
			return 0;
		else if(checkforBombs(c.cur_x-1, c.cur_y) == 1)
			return 0;
		else if(c.cur_x-1 < 0)		//stay in boundaries
			return 0;
		else{
			return 1;
		}
	}
	if(move == 2){		//CHECK MOVE DOWN
	//can't move through other players
		if((c2.cur_x == c.cur_x+1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c1.cur_x == c.cur_x+1 && c1.cur_y == c.cur_y && c1.alive == 1) || (c3.cur_x == c.cur_x+1 && c3.cur_y == c.cur_y && c3.alive == 1))
			return 0;
		if(gameBoard.get_tile(c.cur_x+1, c.cur_y) == SOLID)
			return 0;
		else if(gameBoard.get_tile(c.cur_x+1, c.cur_y) == BREAK)
			return 0;
		else if(checkforBombs(c.cur_x+1, c.cur_y) == 1)
			return 0;
		else if(c.cur_x+1 > 10)		//stay in boundaries
			return 0;
		else
			return 1;
	}
	if(move == 3){		//CHECK MOVE RIGHT
	//can't move through other players
		if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y+1 && c2.alive == 1) || (c1.cur_x == c.cur_x && c1.cur_y == c.cur_y+1 && c1.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y+1 && c3.alive == 1))
			return 0;
		if(gameBoard.get_tile(c.cur_x, c.cur_y+1) == SOLID)
			return 0;
		else if(gameBoard.get_tile(c.cur_x, c.cur_y+1) == BREAK)
			return 0;
		else if(checkforBombs(c.cur_x, c.cur_y+1) == 1)
			return 0;
		else if(c.cur_y+1 > 10)		//stay in boundaries
			return 0;		
		else
			return 1;
	}
	if(move == 4){		//CHECK MOVE LEFT
	//can't move through other players
		if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y-1 && c2.alive == 1) || (c1.cur_x == c.cur_x && c1.cur_y == c.cur_y-1 && c1.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y-1 && c3.alive == 1))
			return 0;
		if(gameBoard.get_tile(c.cur_x, c.cur_y-1) == SOLID)		//can't go through solid blocks
			return 0;
		else if(gameBoard.get_tile(c.cur_x, c.cur_y-1) == BREAK)	//can't move through breakable blocks
			return 0;
		else if(checkforBombs(c.cur_x, c.cur_y-1) == 1)		//can't travel through bombs
			return 0;
		else if(c.cur_y -1 < 0)			//stay in boundaries
			return 0;
		else
			return 1;
	}
}

//check if move is valid for AIPlayer
int Game::checkMove(AIPlayer c, int move){	//1=up,2=down,3=right,4=left
	if(move == 1){		//CHECK MOVE UP
		if(c.name == "c1")		//can't move through other players
			if((c2.cur_x == c.cur_x-1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c3.cur_x == c.cur_x-1 && c3.cur_y == c.cur_y && c3.alive == 1))
				return 0;
		if(c.name == "c2")		//can't move through other players
			if((c1.cur_x == c.cur_x-1 && c1.cur_y == c.cur_y && c1.alive == 1) || (c3.cur_x == c.cur_x-1 && c3.cur_y == c.cur_y && c3.alive == 1))
				return 0;
		if(c.name == "c3")		//can't move through other players
			if((c2.cur_x == c.cur_x-1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c1.cur_x == c.cur_x-1 && c1.cur_y == c.cur_y && c1.alive == 1))
				return 0;
		if(p1.cur_x == c.cur_x-1 && p1.cur_y == c.cur_y && p1.alive == 1)
			return 0;
		if(gameBoard.get_tile(c.cur_x-1, c.cur_y) == SOLID)		//cant move through solid blocks
			return 0;
		else if(gameBoard.get_tile(c.cur_x-1, c.cur_y) == BREAK)	//cant move through breakable blocks
			return 0;
		else if(checkforBombs(c.cur_x-1, c.cur_y) == 1)
			return 0;
		else if(c.cur_x-1 < 0)		//stay in boundaries
			return 0;
		else{
			return 1;
		}
	}
	if(move == 2){		//CHECK MOVE DOWN
		if(c.name == "c1")		//can't move through other players
			if((c2.cur_x == c.cur_x+1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c3.cur_x == c.cur_x+1 && c3.cur_y == c.cur_y && c3.alive == 1))
				return 0;
		if(c.name == "c2")		//can't move through other players
			if((c1.cur_x == c.cur_x+1 && c1.cur_y == c.cur_y && c1.alive == 1) || (c3.cur_x == c.cur_x+1 && c3.cur_y == c.cur_y && c3.alive == 1))
				return 0;
		if(c.name == "c3")		//can't move through other players
			if((c2.cur_x == c.cur_x+1 && c2.cur_y == c.cur_y && c2.alive == 1) || (c1.cur_x == c.cur_x+1 && c1.cur_y == c.cur_y && c1.alive == 1))
				return 0;
		if(p1.cur_x == c.cur_x+1 && p1.cur_y == c.cur_y && p1.alive == 1)
			return 0;
		if(gameBoard.get_tile(c.cur_x+1, c.cur_y) == SOLID)
			return 0;
		else if(gameBoard.get_tile(c.cur_x+1, c.cur_y) == BREAK)
			return 0;
		else if(checkforBombs(c.cur_x+1, c.cur_y) == 1)
			return 0;
		else if(c.cur_x+1 > 10)		//stay in boundaries
			return 0;
		else
			return 1;
	}
	if(move == 3){		//CHECK MOVE RIGHT
		if(c.name == "c1")		//can't move through other players
			if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y+1 && c2.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y+1 && c3.alive == 1))
				return 0;
		if(c.name == "c2")		//can't move through other players
			if((c1.cur_x == c.cur_x && c1.cur_y == c.cur_y+1 && c1.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y+1 && c3.alive == 1))
				return 0;
		if(c.name == "c3")		//can't move through other players
			if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y+1 && c2.alive == 1) || (c1.cur_x == c.cur_x && c1.cur_y == c.cur_y+1 && c1.alive == 1))
				return 0;
		if(p1.cur_x == c.cur_x && p1.cur_y == c.cur_y+1 && p1.alive == 1)
			return 0;
		if(gameBoard.get_tile(c.cur_x, c.cur_y+1) == SOLID)
			return 0;
		else if(gameBoard.get_tile(c.cur_x, c.cur_y+1) == BREAK)
			return 0;
		else if(checkforBombs(c.cur_x, c.cur_y+1) == 1)
			return 0;
		else if(c.cur_y+1 > 10)		//stay in boundaries
			return 0;		
		else
			return 1;
	}
	if(move == 4){		//CHECK MOVE LEFT
		if(c.name == "c1")		//can't move through other players
			if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y-1 && c2.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y-1 && c3.alive == 1))
				return 0;
		if(c.name == "c2")		//can't move through other players
			if((c1.cur_x == c.cur_x && c1.cur_y == c.cur_y-1 && c1.alive == 1) || (c3.cur_x == c.cur_x && c3.cur_y == c.cur_y-1 && c3.alive == 1))
				return 0;
		if(c.name == "c3")		//can't move through other players
			if((c2.cur_x == c.cur_x && c2.cur_y == c.cur_y-1 && c2.alive == 1) || (c1.cur_x == c.cur_x && c1.cur_y == c.cur_y-1 && c1.alive == 1))
				return 0;
		if(p1.cur_x == c.cur_x && p1.cur_y == c.cur_y-1 && p1.alive == 1)
			return 0;
		if(gameBoard.get_tile(c.cur_x, c.cur_y-1) == SOLID)		//can't go through solid blocks
			return 0;
		else if(gameBoard.get_tile(c.cur_x, c.cur_y-1) == BREAK)	//can't move through breakable blocks
			return 0;
		else if(checkforBombs(c.cur_x, c.cur_y-1) == 1)		//can't travel through bombs
			return 0;
		else if(c.cur_y -1 < 0)			//stay in boundaries
			return 0;
		else
			return 1;
	}
}

void Game::multiPlayer(){
}

void Game::printBoard(){
	for(int x=0; x<LEVEL_ROW; x++){
		for(int y=0; y<LEVEL_COL; y++){
			Tile t = gameBoard.get_tile(x, y);
			if(checkforBombs(x,y) == 1)
				printf("O");
			else if(c1.cur_x == x && c1.cur_y == y && c1.alive == 1)
				printf("1");
			else if(c2.cur_x == x && c2.cur_y == y && c2.alive == 1)
				printf("2");
			else if(c3.cur_x == x && c3.cur_y == y && c3.alive == 1)
				printf("3");
			else if(p1.cur_x == x && p1.cur_y == y && p1.alive == 1)
				printf("*");
			else if(t == GROUND)
				printf(" ");
			else if(t == SOLID)
				printf("I");
			else if(t == BREAK)
				printf("B");
		}
		printf("\n");
	}
	cout << endl << "Scores: " << endl;
	cout << p1.name << " = " << p1.myScore.getScore() << endl;
 	cout << "c1 = " << c1.myScore.getScore() << endl;
	cout << "c2 = " << c2.myScore.getScore() << endl;
	cout << "c3 = " << c3.myScore.getScore() << endl << endl;
}

//requires error checking in calling function to ensure:
//1) player still has bombs left
//2) another bomb is not in same location
//calling function must also decrement maxbombs
void Game::setBomb(string n, int r, int x, int y){
	
	Bomb tempB;
	tempB.killer_name = n;
	tempB.radius = r;
	tempB.timer = 4;	//goes off after 3 moves
	tempB.loc_x = x;
	tempB.loc_y = y;
	bombs.push_back(tempB);
	//gameBoard.update(x, y, BOMB);
}

void Game::bombDec(){
	int x = 0;
	int count;
	while(x < bombs.size()) {
		bombs[x].timer = bombs[x].timer -1;
		if(bombs[x].timer == 0){
			//gameBoard.update(bombs[x].loc_x, bombs[x].loc_y, GROUND);
			blowUp(bombs[x]);
			bombs.erase(bombs.begin()+x);
		}
		else
			x++;
	}
}

void Game::kill(string n, string victim){
	if(victim != n){
	if(n == p1.name){
		p1.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else if(n == c1.name){
		c1.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else if(n == c2.name) {
		c2.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	else {
		c3.myScore.score_kill();
		cout << n << " killed " << victim << endl;}
	}
	else
		cout << "Dumbass " << victim << " killed himself" << endl;
}

void Game::blowUp(Bomb b){
	//blow up walls
	int x = b.loc_x;
	int y = b.loc_y;
	int count = b.radius+1;
	Tile t = gameBoard.get_tile(x,y);
	//up
	while(t != SOLID && x > 0 && count > 0){
		t = gameBoard.get_tile(x,y);
		if(t == BREAK)
			gameBoard.update(x,y, GROUND);
		if(c1.cur_x == x && c1.cur_y == y && c1.alive == 1){
			c1.alive = 0;
			updateScores(0);
			kill(b.killer_name, c1.name);}
		if(c2.cur_x == x && c2.cur_y == y && c2.alive == 1){
			c2.alive = 0;
			updateScores(0);
			kill(b.killer_name, c2.name);}
		if(c3.cur_x == x && c3.cur_y == y && c3.alive == 1){
			c3.alive = 0;
			updateScores(0);
			kill(b.killer_name, c3.name);}
		if(p1.cur_x == x && p1.cur_y == y && p1.alive == 1){
			p1.alive = 0;
			updateScores(0);
			kill(b.killer_name, p1.name);}
		x--;
		count--;
	}
	count = b.radius+1;
	x = b.loc_x;
	t = gameBoard.get_tile(x,y);
	while(t != SOLID && x < 11 && count > 0){
		t = gameBoard.get_tile(x,y);
		if(t == BREAK)
			gameBoard.update(x,y, GROUND);
		if(c1.cur_x == x && c1.cur_y == y && c1.alive == 1){
			c1.alive = 0;
			updateScores(0);
			kill(b.killer_name, c1.name);}
		if(c2.cur_x == x && c2.cur_y == y && c2.alive == 1){
			c2.alive = 0;
			updateScores(0);
			kill(b.killer_name, c2.name);}
		if(c3.cur_x == x && c3.cur_y == y && c3.alive == 1){
			c3.alive = 0;
			updateScores(0);
			kill(b.killer_name, c3.name);}
		if(p1.cur_x == x && p1.cur_y == y && p1.alive == 1){
			p1.alive = 0;
			updateScores(0);
			kill(b.killer_name, p1.name);}
		x++;
		count--;
	}
	count = b.radius+1;
	x = b.loc_x;
	t = gameBoard.get_tile(x,y);
	while(t != SOLID && y < 11 && count >0){
		t = gameBoard.get_tile(x,y);
		if(t == BREAK)
			gameBoard.update(x,y, GROUND);
		if(c1.cur_x == x && c1.cur_y == y && c1.alive == 1){
			c1.alive = 0;
			updateScores(0);
			kill(b.killer_name, c1.name);}
		if(c2.cur_x == x && c2.cur_y == y && c2.alive == 1){
			c2.alive = 0;
			updateScores(0);
			kill(b.killer_name, c2.name);}
		if(c3.cur_x == x && c3.cur_y == y && c3.alive == 1){
			c3.alive = 0;
			updateScores(0);
			kill(b.killer_name, c3.name);}
		if(p1.cur_x == x && p1.cur_y == y && p1.alive == 1){
			p1.alive = 0;
			updateScores(0);
			kill(b.killer_name, p1.name);}
		y++;
		count--;
	}
	count = b.radius+1;
	y = b.loc_y;
	t = gameBoard.get_tile(x,y);
	while(t != SOLID && y > 0 && count >0){
		t = gameBoard.get_tile(x,y);
		if(c1.cur_x == x && c1.cur_y == y && c1.alive == 1){
			c1.alive = 0;
			updateScores(0);
			kill(b.killer_name, c1.name);}
		if(c2.cur_x == x && c2.cur_y == y && c2.alive == 1){
			c2.alive = 0;
			updateScores(0);
			kill(b.killer_name, c2.name);}
		if(c3.cur_x == x && c3.cur_y == y && c3.alive == 1){
			c3.alive = 0;
			updateScores(0);
			kill(b.killer_name, c3.name);}
		if(p1.cur_x == x && p1.cur_y == y && p1.alive == 1){
			p1.alive = 0;
			updateScores(0);
			kill(b.killer_name, p1.name);}
		if(t == BREAK)
			gameBoard.update(x,y, GROUND);
		y--;
		count--;
	}
	count = b.radius+1;
	y = b.loc_y;
	t = gameBoard.get_tile(x,y);
}

//used to update the scores of all players based
//on who's alive and the time
//
//if n == 1, all players alive receive score += 1
//else, updateScores awards points to players for being the last, last 2, or last 3
//players left alive in the game
void Game::updateScores(int n){
	if(n == 1) {
		if(c1.alive == 1)
			c1.myScore.score_inc(1);
		if(c2.alive == 1)
			c2.myScore.score_inc(1);
		if(c3.alive == 1)
			c3.myScore.score_inc(1);
		if(p1.alive == 1)
			p1.myScore.score_inc(1);
	}
	else{
	int total = c1.alive + c2.alive + c3.alive + p1.alive;	//determine how many are alive
	if(total == 1){		//determine which player was the last one alive
		if(c1.alive == 1){
			c1.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c1 has won the match with score: " << c1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c2.alive == 1){
			c2.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c2 has won the match with score: " << c2.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else if(c3.alive == 1){
			c3.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << "c3 has won the match with score: " << c3.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
		else{
			p1.myScore.score_lastAlive();
			printBoard();
			cout << "WINNER!!!" << endl;
			cout << p1.name << " has won the match with score: " << p1.myScore.getScore() << endl << endl;
			saveScores();
			exit(1);
		}
	}
	if(total == 2){		//2 players are left alive
		if(c1.alive == 1 && c2.alive == 1){
			c1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(c1.alive == 1 && c3.alive == 1){
			c1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(c2.alive == 1 && c3.alive == 1){
			c2.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c1.alive == 1){
			p1.myScore.score_2Alive();
			c1.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c2.alive == 1){
			p1.myScore.score_2Alive();
			c2.myScore.score_2Alive();
		}
		else if(p1.alive == 1 && c3.alive == 1){
			p1.myScore.score_2Alive();
			c3.myScore.score_2Alive();
		}
	}
	if(total == 3){		//3 players are left alive
		if(p1.alive == 0){
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();}
		else if(c1.alive == 0){
			p1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else if(c2.alive == 0){
			c1.myScore.score_3Alive();
			p1.myScore.score_3Alive();
			c3.myScore.score_3Alive();
		}
		else{
			c1.myScore.score_3Alive();
			c2.myScore.score_3Alive();
			p1.myScore.score_3Alive();
		}
	} }
}



//needs to be filled out to display proper AI animation
void Game::displayAI(AIPlayer ai){
	if(ai.latestMove == 1){
		//DISPLAY AI PLAYER MOVING UP
	}
	else if(ai.latestMove == 2){
		//DISPLAY AI PLAYER MOVING DOWN
	}
	else if(ai.latestMove == 3){
		//DISPLAY AI PLAYER MOVING RIGHT
	}
	else {
		//DISPLAY AI PLAYER MOVING LEFT
	}
}



void Game::saveScores(){
	Highscore h1;
	h1.readScores();
	h1.writeNewScore(p1.myScore.getScore());
	h1.writeNewScore(c1.myScore.getScore());
	h1.writeNewScore(c2.myScore.getScore());
	h1.writeNewScore(c3.myScore.getScore());
}

int main() {
	//assume game is single player vs. AI
	cout << "|   | |  _____  __   __      __   __  |---|  __        |  __   __   __     | |" << endl;
	cout << "|   | |    |   |__| |__| __ |__| |  | | | | |__| __  __| |__| |  | |__| __ | |" << endl;
	cout << "|___| |__  |   | |  |  |    |__| |__| |   | |__|    |__| | |  |__| |       | |" << endl;
	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
	cout << " _____       __   __   __	 **********************************" << endl;
	cout << "   |   |  | |__| |__| |  | ****************************************" << endl;
	cout << "   |   |__| | |  |__| |__| ****************************************" << endl << endl;
	Game* newGame = new Game();
	int rad;
	string s;
	cout << "Set Radius of bomb (1 to 11): ";
	cin >> s;
	istringstream( s ) >> rad;

	cout << "Your name: ";
	cin >> s;
	newGame->setLocalName(s);

	newGame->setBombRadius(rad);
	newGame->singlePlayer();
	return 0;
}
