/**************************************************
 Author: Jacob Barca
 Purpose: Player Code File
 The Player class' code file
**************************************************/

#include "Player.h"

/*
Main constructor: initialises playerName to given value and sets defaults
for all other values.
*/
Player::Player(string name) {
	playerName = name;
	playerSkillLevel = 0;
	playerScore = 0;
	gamesPlayed = 0;
	gamesWon = 0;
	lossStreak = 0;
	winLossRatio = 0.0f;
	gameMode = NUMBERS;
}

/*
Destructor: not used yet.
*/
Player::~Player() {}

/*
Returns the player's name.
*/
string Player::getName() {
	return playerName;
}

/*
Returns the player's score.
*/
int Player::getScore() {
	return playerScore;
}

/*
Returns the player's skill level.
*/
int Player::getSkillLevel() {
	return playerSkillLevel;
}

/*
Returns the number of games the player has played.
*/
int Player::getGamesPlayed() {
	return gamesPlayed;
}

/*
Returns the current loss streak.
*/
int Player::getLossStreak() {
	return lossStreak;
}

/*
Returns the win/loss ratio of the player (as a percentage).
*/
float Player::getWinLossRatio() {
	return winLossRatio;
}

/*
Returns the number of games the player has won.
*/
int Player::getGamesWon() {
	return gamesWon;
}

/*
Returns the game mode the player has chosen.
*/
Player::GameMode Player::getGameMode() {
	return gameMode;
}

/*
Returns a formatted string containing all of the player's statistics.
*/
string Player::getPlayerStatistics() {
	stringstream displayText;

	displayText << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	displayText << " Name: \t\t\t" << getName() << "\n";
	displayText << " Rank: \t\t\t" << getSkillLevel() << "\n";
	displayText << " Score: \t\t" << getScore() << "\n";
	displayText << " Games Played: \t\t" << getGamesPlayed() << "\n";
	displayText << " Games Won: \t\t" << getGamesWon() << "\n";
	displayText << " Win/Loss Ratio: \t" << getWinLossRatio() << "%\n";
	displayText << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return displayText.str();
}

/*
Sets the player's skill level to the given value.
*/
void Player::setSkillLevel(int skillLevel) {
	if (skillLevel >= 1 && skillLevel <= 3) {
		playerSkillLevel = skillLevel;
		lossStreak = 0;
	}
}

/*
Sets the player's game mode to the specified type.
*/
void Player::setGameMode(GameMode type) {
	gameMode = type;
}

/*
Updates the player's score to the given value.
*/
void Player::updateScore(int score) {
	if (score >= 0) {
		playerScore = score;
	}

	else {
		playerScore = 0;
	}
}

/*
Increments the number of games played.
*/
void Player::updateGamesPlayed() {
	gamesPlayed++;
}

/*
Increments the player's loss streak when a player loses a game
*/
void Player::updateLossStreak() {
	lossStreak++;
}

/*
Calculates the win/loss ratio and converts it to a percentage.
*/
void Player::updateWinLossRatio() {
	if (gamesPlayed > 0) {
		// convert integers to floats and calculate percentage
		winLossRatio = (static_cast<float>(gamesWon) /
			static_cast<float>(gamesPlayed)) * 100.0f;
	}
}

/*
Increments the number of games won. Sets the loss streak to 0.
*/
void Player::updateGamesWon() {
	gamesWon++;
	lossStreak = 0;
}