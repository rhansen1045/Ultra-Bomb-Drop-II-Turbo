#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "Highscore.h"


Highscore::Highscore(){
	int a=0;
}

void Highscore::readScores(){
	//cout << "Reading top 10 scores....." << endl;
	FILE *filep;
	filep = fopen("scores.txt", "r");
	if(filep ==0)
		printf("Could not open file\n");
	else{
	int x, y;
	bool b = false;
	char c;
	string tempstring;
	y =0;
	while((x=fgetc(filep))!= EOF){
		c = (char)x;
		if(c == 'S'){
			if(y > 0){
				scores[y-1] = tempstring;}
			tempstring = "";
			y++;
			b = false;
		}
		if(c != '1' || c != '2' || c != '3' || c != '4' || c != '5' || c != '6' || c != '7' || c != '8' || c != '9' || c != '0' && y == 10)
			scores[9] = tempstring;
		if(b==true && (c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9' || c=='0')){
			tempstring += c;
		}
		if(c == '='){
			b = true;
			}
	}
	//for(int z =0; z < 10; z++)
	//	cout << "SCORE NUMBER " << z+1 << ": " << scores[z] << endl;
	fclose(filep);
	}
}

void Highscore::writeNewScore(int score){
	//cout << "Writing new score of " << score << "....." << endl;
	FILE *filep;
	filep = fopen("scores.txt", "r");
	if(filep ==0)
		printf("Could not open file\n");
	else{		//first reads all scores on stores in an array
		int x = 0;
		bool b = false;
		
		//find place to put into list
		while (b==false && x < 10){
			if(score > atoi(scores[x].c_str()) )
				b = true;
			else
				x++;
		} 
		if(b==true){
			cout << "Writing new high score of " << score << " in top 10" << endl;
		for(int y = 9; y > x; y--){
			scores[y] = scores[y-1];}
		string s = boost::lexical_cast<string>(score);
		scores[x] = s;
		}
		else
			cout << "SCORE NOT GOOD ENOUGH FOR TOP 10" << endl;
	}
	//for(int z =0; z < 10; z++)
	//	cout << "SCORE NUMBER " << z+1 << ": " << scores[z] << endl;
	cout << endl;
	fclose(filep);
	ofstream myfile;
	myfile.open("scores.txt");
	myfile << "SCORE1=" << scores[0] << "\n";
	myfile << "SCORE2=" << scores[1] << "\n";
	myfile << "SCORE3=" << scores[2] << "\n";
	myfile << "SCORE4=" << scores[3] << "\n";
	myfile << "SCORE5=" << scores[4] << "\n";
	myfile << "SCORE6=" << scores[5] << "\n";
	myfile << "SCORE7=" << scores[6] << "\n";
	myfile << "SCORE8=" << scores[7] << "\n";
	myfile << "SCORE9=" << scores[8] << "\n";
	myfile << "SCORE0=" << scores[9] << "\n";
	myfile.close();
}

string Highscore::getScoreString(int x){
	return scores[x];
}

int Highscore::getScore(int x){
	return atoi(scores[x].c_str());
}

string* Highscore::getScores(){
	return scores;
}

void Highscore::overwriteScore(int place, int score){
	cout << "OVERWRITING SCORE " << scores[place] << " WITH " << score << endl;
	string s = boost::lexical_cast<string>(score);
	scores[place] = s;
	ofstream myfile;
	myfile.open("scores.txt");
	myfile << "SCORE1=" << scores[0] << "\n";
	myfile << "SCORE2=" << scores[1] << "\n";
	myfile << "SCORE3=" << scores[2] << "\n";
	myfile << "SCORE4=" << scores[3] << "\n";
	myfile << "SCORE5=" << scores[4] << "\n";
	myfile << "SCORE6=" << scores[5] << "\n";
	myfile << "SCORE7=" << scores[6] << "\n";
	myfile << "SCORE8=" << scores[7] << "\n";
	myfile << "SCORE9=" << scores[8] << "\n";
	myfile << "SCORE0=" << scores[9] << "\n";
	myfile.close();
}

void Highscore::resetScores(){
	cout << "SCORES RESET" << endl;
	for(int x =0; x < 10; x++)
		scores[x] = "0";
	ofstream myfile;
	myfile.open("scores.txt");
	myfile << "SCORE1=" << scores[0] << "\n";
	myfile << "SCORE2=" << scores[1] << "\n";
	myfile << "SCORE3=" << scores[2] << "\n";
	myfile << "SCORE4=" << scores[3] << "\n";
	myfile << "SCORE5=" << scores[4] << "\n";
	myfile << "SCORE6=" << scores[5] << "\n";
	myfile << "SCORE7=" << scores[6] << "\n";
	myfile << "SCORE8=" << scores[7] << "\n";
	myfile << "SCORE9=" << scores[8] << "\n";
	myfile << "SCORE0=" << scores[9] << "\n";
	myfile.close();
}
