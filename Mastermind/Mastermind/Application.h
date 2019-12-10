/**************************************************
 Author: Jacob Barca
 Purpose: Application Header File
 The Application class' header file
**************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Board.h"
#include "Computer.h"

using namespace std;

Player* player;
Computer* computer;
Board* board;

const int MAX_ELEMENTS = 10;
const string numbers[MAX_ELEMENTS] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
const string symbols[MAX_ELEMENTS] = { "!", "@", "#", "$", "%", "&", "*", ">", "<", "?" };

void createPlayers();
void createBoard();
void displayTitle();
void displayIntro();
void displayPossibleElements(Player::GameMode gameMode);
void resetGame();
void calculateClues(vector<string>& userCode, vector<string>& hiddenCode);
vector<string> indexToCode(Player::GameMode gameMode, string code);
vector<string> loadWords(string fileName);
void playMastermind();
void changeSkillLevel(int newSkillLevel);
int calculateScore(int numTurns);
void displayStatistics();
void updatePlayerStatistics();
bool checkGameOver(vector<string>& userCode, vector<string>& hiddenCode);
void gameOver(vector<string>& userCode, vector<string>& hiddenCode);
void deletePointers();

string askForString(string question);
vector<string> askForCode(string question, Player::GameMode gameMode);
int askForNumber(string question, int min, int max);
char askForLetter(string question);

#endif
