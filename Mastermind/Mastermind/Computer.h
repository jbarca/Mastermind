/**************************************************
 Author: Jacob Barca
 Purpose: Computer Header File
 The Computer class' header file
**************************************************/

#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "Player.h"

class Computer : public Player {
public:
	// constructors
	Computer();

	// destructors
	~Computer();

	// mutators / quasi-mutators
	string createCode(Player::GameMode gameMode, int skillLevel);
	void randomiseWord(int boardRows, int boardColumns, int skillLevel);
	void chooseRandomWord(vector<string> wordList, int skillLevel);

	// accessors
	string getRandomWord();
	string getJumbledWord();
	string getPlayerStatistics();

private:
	// private instance variables
	string randomWord;
	string jumbledWord;


};

#endif

