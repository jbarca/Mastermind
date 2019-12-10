/**************************************************
 Author: Jacob Barca
 Purpose: Player Header File
 The Player class' header file
**************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sstream>

using namespace std;

class Player {
public:
	enum GameMode { NUMBERS, SYMBOLS, WORDS };

	// constructors
	Player(string name);

	// destructors
	~Player();

	// accessors
	string getName();
	int getScore();
	int getSkillLevel();
	int getGamesPlayed();
	int getLossStreak();
	float getWinLossRatio();
	int getGamesWon();
	GameMode getGameMode();
	virtual string getPlayerStatistics();

	// mutators and quasi-mutators
	void setSkillLevel(int skillLevel);
	void setGameMode(GameMode type);
	void updateScore(int score);
	void updateGamesPlayed();
	void updateLossStreak();
	void updateWinLossRatio();
	void updateGamesWon();

protected:
	// private variables
	string playerName;
	GameMode gameMode;
	int playerSkillLevel;
	int playerScore;
	int gamesPlayed;
	int gamesWon;
	int lossStreak;
	float winLossRatio;
};

#endif


