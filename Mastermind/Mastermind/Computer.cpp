/**************************************************
 Author: Jacob Barca
 Purpose: Computer Code File
 The Computer class' code file
**************************************************/

#include "Computer.h"

/*
Initialises a computer instance with super constructor
*/
Computer::Computer() : Player("Computer") {
	randomWord = "";
	jumbledWord = "";
}

/*
Destructor: not used yet
*/
Computer::~Computer() {}

/*
Creates a random code using symbols/numbers and in the case of a word
it chooses the word as normal.
*/
string Computer::createCode(Player::GameMode gameMode, int skillLevel) {
	int maxIndex = skillLevel + 3;
	int randomIndex = 0;
	string hiddenCode = "";

	for (int i = 0; i < maxIndex; i++) {
		if (gameMode == Player::GameMode::NUMBERS || gameMode ==
			Player::GameMode::SYMBOLS) {
			randomIndex = rand() % maxIndex;
			hiddenCode += to_string(randomIndex);
		}
		else if (gameMode == Player::GameMode::WORDS) {
			hiddenCode += to_string(i);
		}
	}

	return hiddenCode;

}

/*
Randomises the randomly chosen word such that all the letters in the jumbled
word are distinct and the player can choose more characters that may not even
be in the word.
*/
void Computer::randomiseWord(int boardRows, int boardColumns, int skillLevel) {
	int numExtraLetters = boardRows - 4 - boardColumns;
	string newWord = "";
	string randomChar = "";

	for (int i = 0; i < boardColumns; i++) {
		if (newWord.find(randomWord[i]) == string::npos) {
			newWord += randomWord[i];
		}
		else {
			randomChar = string(1, 'a' + rand() % 26);
			while (newWord.find(randomChar) != string::npos) {
				randomChar = string(1, 'a' + rand() % 26);
			}
			newWord += randomChar;
		}
	}

	for (int i = 0; i < numExtraLetters; i++) {
		randomChar = string(1, 'a' + rand() % 26);
		while (newWord.find(randomChar) != string::npos) {
			randomChar = string(1, 'a' + rand() % 26);
		}
		newWord += randomChar;
	}
	jumbledWord = newWord;
	random_shuffle(jumbledWord.begin(), jumbledWord.end());
}

/*
Chooses a random word based on the player's skill level. Sets the jumbled
word equal to the random word.
*/
void Computer::chooseRandomWord(vector<string> wordList, int skillLevel) {
	// choose a random word between the range the player's skill level is at
	// if skill level = 1, choose 4 letter word (0 to (1/3))
	// skill level = 2, 5 letter word ((1/3) to (2/3))
	// skill level = 3, 6 letter word ((2/3) to 1)
	int startRange = (int)((skillLevel - 1) * (1.0 / 3.0) * wordList.size());
	int endRange = (int)(skillLevel * (1.0 / 3.0) * wordList.size() - startRange);
	int randomWordIndex = rand() % endRange + startRange;
	randomWord = wordList[randomWordIndex];
	jumbledWord = randomWord;
}

/*
Returns the randomly chosen word
*/
string Computer::getRandomWord() {
	return randomWord;
}

/*
Returns the jumbled word
*/
string Computer::getJumbledWord() {
	return jumbledWord;
}

/*
Overriden from Player.
Returns a formatted string containing all of the player's statistics.
*/
string Computer::getPlayerStatistics() {
	stringstream displayText;

	displayText << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	displayText << " Name: \t\t\t" << getName() << "\n";
	displayText << " Score: \t\t" << getScore() << "\n";
	displayText << " Games Played: \t\t" << getGamesPlayed() << "\n";
	displayText << " Games Won: \t\t" << getGamesWon() << "\n";
	displayText << " Win/Loss Ratio: \t" << getWinLossRatio() << "%\n";
	displayText << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

	return displayText.str();
}

