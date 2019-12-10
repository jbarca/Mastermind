/**************************************************
 Author: Jacob Barca
 Purpose: Application Code File
 The Application class' code file
**************************************************/

#include "Application.h"

int main() {
	// seed randoms
	srand(unsigned(time(NULL)));
	// display introduction
	displayIntro();
	// get user input
	createPlayers();
	// run MasterMind
	playMastermind();
	// deallocate memory
	deletePointers();
	// wait and exit
	system("pause");
	return 0;
}

/*
Displays the title in ASCII art from a text file.
*/
void displayTitle() {
	ifstream titleFile("title.txt");
	string line = "";

	if (titleFile.is_open()) {
		while (!titleFile.eof()) {
			getline(titleFile, line);
			cout << line << endl;
		}
	}

	titleFile.close();
}

/*
Creates both the human player and the computer player and initialises their
statistics.
*/
void createPlayers() {
	// Create computer player
	computer = new Computer();

	string userInput = "";
	int userSkill = 0;
	int userGameMode = 0;
	system("cls");

	displayTitle();
	userInput = askForString("\nPlease enter your name: ");

	// new Player object gets allocated in the heap so it can be 
	// referenced from outside this function.
	player = new Player(userInput);
	userSkill = askForNumber("\nPlease select a skill level to play at:\n[0] Easy (10 rows x 4 columns),\n[1] Medium (12 rows x 5 columns)\n[2] Hard (14 rows x 6 columns)\nYour choice: ", 0, 2);
	player->setSkillLevel(userSkill + 1);
	userGameMode = askForNumber("\nPlease select the game mode you would like to play:\n[0] Numbers\n[1] Symbols\n[2] Words\nYour choice: ", 0, 2);
	player->setGameMode((Player::GameMode)userGameMode);
	cout << "\nThank you, " << player->getName() << ". Good luck!\n";
	cout << "\n";
	displayStatistics();
	computer->chooseRandomWord(loadWords("words.txt"), player->getSkillLevel());
	createBoard();
	system("pause");
}

/*
Displays both the computer player's and human player's current statistics
*/
void displayStatistics() {
	cout << player->getPlayerStatistics() << "\n\n";
	cout << computer->getPlayerStatistics() << "\n";
}

/*
Updates the computer player's and the human player's statistics
*/
void updatePlayerStatistics() {
	int currentRows = board->getCurrentRows();
	int playerScore = calculateScore(currentRows);

	player->updateGamesPlayed();
	player->updateScore(player->getScore() + playerScore);
	player->updateWinLossRatio();

	computer->updateGamesPlayed();
	computer->updateScore(computer->getScore() + (100 - playerScore));
	computer->updateWinLossRatio();
}

/*
Creates the initial board that the player will play on.
*/
void createBoard() {
	Player::GameMode gameMode = player->getGameMode();
	int skillLevel = player->getSkillLevel();
	vector<string> hiddenCode = indexToCode(gameMode, computer->createCode(gameMode, skillLevel));
	board = new Board(skillLevel * 2 + 8, skillLevel + 3, hiddenCode);
}

/*
Displays the intro text contained in the introduction file.
*/
void displayIntro() {
	displayTitle();

	ifstream introductionFile("introduction.txt");
	string line = "";

	if (introductionFile.is_open()) {
		while (!introductionFile.eof()) {
			getline(introductionFile, line);
			cout << line << endl;
		}
	}
	introductionFile.close();

	system("pause");
}

/*
Displays all of the possible elements that the player can choose
to make their code.
*/
void displayPossibleElements(Player::GameMode gameMode) {
	int numElements = board->getBoardRows() - 4;
	string jumbledWord = computer->getJumbledWord();
	cout << "Possible code elements: ";
	for (int i = 0; i < numElements; i++) {
		if (gameMode == Player::GameMode::NUMBERS) {
			if (i == numElements - 1) {
				cout << numbers[i] << " [" << i << "]";
			}
			else {
				cout << numbers[i] << " [" << i << "]" << ", ";
			}
		}
		else if (gameMode == Player::GameMode::SYMBOLS) {
			if (i == numElements - 1) {
				cout << symbols[i] << " [" << i << "]";
			}
			else {
				cout << symbols[i] << " [" << i << "]" << ", ";
			}
		}
		else if (gameMode == Player::GameMode::WORDS) {
			if (i == numElements - 1) {
				cout << jumbledWord[i] << " [" << i << "]";
			}
			else {
				cout << jumbledWord[i] << " [" << i << "]" << ", ";
			}
		}
	}
	cout << "\n";
	cout << "Type [q] to quit\n\n";
}

/*
Resets the board to it's initial state (empty) and creates a new hidden code
for the board.
*/
void resetGame() {
	int skillLevel = player->getSkillLevel();
	Player::GameMode gameMode = player->getGameMode();
	computer->chooseRandomWord(loadWords("words.txt"), skillLevel);
	vector<string> hiddenCode = indexToCode(gameMode, computer->createCode(gameMode, skillLevel));
	board->resetBoard(hiddenCode);
}

/*
Calculates the clues based on the human player's code and stores them in
the userCode vector.
*/
void calculateClues(vector<string>& userCode, vector<string>& hiddenCode) {
	int boardCols = board->getBoardColumns();
	vector<bool> found(boardCols, false);
	int index = boardCols;

	for (unsigned int i = 0; i < hiddenCode.size(); i++) {
		if (userCode[i] == hiddenCode[i]) {
			userCode[index] = "o";
			found[i] = true;
			index++;
		}
	}

	for (unsigned int i = 0; i < hiddenCode.size(); i++) {
		if (!found[i]) {
			for (unsigned int j = 0; j < hiddenCode.size(); j++) {
				if (!found[j] && userCode[i] == hiddenCode[j]) {
					userCode[index] = "?";
					found[i] = true;
					index++;
				}
			}
		}
	}
}

/*
Converts a string of indices into a vector containing the code elements
that the user has selected.
*/
vector<string> indexToCode(Player::GameMode gameMode, string code) {
	int index = 0;
	int numElements = 6;
	string jumbledWord = computer->getJumbledWord();
	vector<string> codeElements;
	for (unsigned int i = 0; i < code.length(); i++) {
		index = stoi(string(1, code[i]));
		if (gameMode == Player::GameMode::NUMBERS) {
			codeElements.push_back(numbers[index]);
		}
		else if (gameMode == Player::GameMode::SYMBOLS) {
			codeElements.push_back(symbols[index]);
		}
		else if (gameMode == Player::GameMode::WORDS) {
			codeElements.push_back(string(1, jumbledWord[index]));
		}
	}

	return codeElements;
}

/*
Loads all the words in the word list into a words vector and returns it.
*/
vector<string> loadWords(string fileName) {
	ifstream wordsFile(fileName);
	vector<string> words;
	string line = "";

	if (wordsFile.is_open()) {
		while (!wordsFile.eof()) {
			getline(wordsFile, line);
			words.push_back(line);
		}
	}
	wordsFile.close();
	return words;
}

/*
The main game functionality and logic for Mastermind.
*/
void playMastermind() {
	bool quit = false;
	bool hasQuitGame = false;
	int skillLevel = player->getSkillLevel();
	int boardCols = board->getBoardColumns();
	vector<string> hiddenCode = board->getHiddenCode();
	vector<string> userCode;
	computer->randomiseWord(board->getBoardRows(), boardCols, skillLevel);

	while (!quit) {
		system("cls");
		displayTitle();
		cout << board->displayBoard() << endl;
		displayPossibleElements(player->getGameMode());
		userCode = askForCode("Please enter a code: ", player->getGameMode());

		if (userCode[0] == "q") {
			quit = true;
			hasQuitGame = true;
		}

		else if (!checkGameOver(userCode, hiddenCode)) {
			// Add clues to userCode
			calculateClues(userCode, hiddenCode);
			// Add the row to the board
			board->createRow(userCode);
		}
		else {
			quit = true;
		}
	}

	if (!hasQuitGame) {
		gameOver(userCode, hiddenCode);
	}
	else {
		cout << "Thanks for playing, " << player->getName() << ".\n";
	}
}

/*
Either promotes or demotes the player based on the value of newSkillLevel.
The old board is deleted from memory and a new board with new dimensions takes
it's place.
*/
void changeSkillLevel(int newSkillLevel) {
	Player::GameMode gameMode = player->getGameMode();
	vector<string> hiddenCode;

	if (newSkillLevel >= 1 && newSkillLevel <= 3) {
		player->setSkillLevel(newSkillLevel);
		computer->chooseRandomWord(loadWords("words.txt"), newSkillLevel);
		hiddenCode = indexToCode(gameMode, computer->createCode(gameMode, newSkillLevel));
		delete board;
		board = new Board(newSkillLevel * 2 + 8, newSkillLevel + 3, hiddenCode);
	}
}

/*
The scoring system used to calculate the players' scores. Gives 100 as the max
score per game which includes a bonus for unused rows. The minimum score a player
can get is 7.
*/
int calculateScore(int numTurns) {
	if (numTurns > 0) {
		return (int)((1.0 / numTurns) * 100);
	}
	else {
		return 0;
	}
}

/*
Checks if the end game conditions have been met, in which case the game
is over.
*/
bool checkGameOver(vector<string>& userCode, vector<string>& hiddenCode) {
	return equal(userCode.begin(), userCode.begin() + board->getBoardColumns(),
		hiddenCode.begin()) || board->getCurrentRows() + 1 >= board->getBoardRows();
}

/*
Handles the post-game logic. Promotion and demotion is also performed in this
function as well as restarting the game or quitting the game.
*/
void gameOver(vector<string>& userCode, vector<string>& hiddenCode) {
	system("cls");
	char response = ' ';
	displayTitle();

	calculateClues(userCode, hiddenCode);
	board->createRow(userCode);
	cout << board->displayBoard(true) << endl;

	if (equal(userCode.begin(), userCode.begin() + board->getBoardColumns(),
		hiddenCode.begin())) {
		cout << "\nCongratulations, you win!\n\n";
		player->updateGamesWon();
		updatePlayerStatistics();

		if (player->getGamesWon() % 5 == 0 && player->getSkillLevel() < 3) {
			response = askForLetter("Do you want to be promoted? (y/n): ");
			while (response != 'y' && response != 'n') {
				cout << "Invalid input!\n";
				response = askForLetter("Do you want to be promoted? (y/n): ");
			}
			if (response == 'y') {
				cout << "\nYou were promoted!\n";
				cout << "Rank " << player->getSkillLevel() << " --> Rank "
					<< player->getSkillLevel() + 1;
				changeSkillLevel(player->getSkillLevel() + 1);
			}
			else {
				resetGame();
			}
			cout << "\n\n";
		}
		else {
			resetGame();
		}
	}

	else {
		computer->updateGamesWon();
		updatePlayerStatistics();
		cout << "\nGame over!\n\n";

		if (player->getLossStreak() >= 5 && player->getSkillLevel() > 1) {
			cout << "\nYou were demoted!\n";
			cout << "Rank " << player->getSkillLevel() << " --> Rank "
				<< player->getSkillLevel() - 1;
			changeSkillLevel(player->getSkillLevel() - 1);
			cout << "\n\n";
		}
		else {
			player->updateLossStreak();
			resetGame();
		}
	}
	displayStatistics();

	response = askForLetter("Do you want to play again? (y/n): ");
	while (response != 'y' && response != 'n') {
		cout << "Invalid input!\n";
		response = askForLetter("Do you want to play again? (y/n): ");
	}

	if (response == 'y') {
		playMastermind();
	}
	else {
		cout << "Thanks for playing, " << player->getName() << ".\n";
	}
}

/*
Deletes all of the pointers from the heap and sets them to null so that they are
freed from memory.
*/
void deletePointers() {
	delete player;
	delete board;
	delete computer;
	player = NULL;
	board = NULL;
	computer = NULL;
}

/*
Asks the user for a string and returns the result once it is validated.
*/
string askForString(string question) {
	string userInput = "";
	bool quit = false;

	while (!quit) {
		cout << question;
		getline(cin, userInput);

		if (userInput != "") {
			quit = true;
		}
		else {
			cout << "Invalid input!\n";
		}
	}

	return userInput;
}

/*
Asks the user for a specific code and once it is validated, returns it.
*/
vector<string> askForCode(string question, Player::GameMode gameMode) {
	string userInput = "";
	bool quit = false;
	bool isValid = true;
	int index = 0;
	bool isDigitString = false;
	int numElements = board->getBoardRows() - 4;
	vector<string> codeElements;

	while (!quit) {
		isValid = true;
		isDigitString = true;
		cout << question;
		getline(cin, userInput);

		for (unsigned int i = 0; i < userInput.length(); i++) {
			if (!isdigit(userInput[i])) {
				isDigitString = false;
			}
		}

		if (isDigitString && userInput.length() == board->getBoardColumns()) {
			for (unsigned int i = 0; i < userInput.length(); i++) {
				index = stoi(string(1, userInput[i]));
				if (index < 0 || index >= numElements) {
					isValid = false;
				}
			}

			if (isValid) {
				quit = true;
			}
			else {
				cout << "Invalid input!\n";
			}
		}

		else if (userInput == "q") {
			return vector<string> {"q"};
		}

		else {
			cout << "Invalid input!\n";
		}
	}

	codeElements = indexToCode(gameMode, userInput);

	for (unsigned int i = 0; i < userInput.length(); i++) {
		codeElements.push_back(" ");
	}

	return codeElements;
}

/*
Asks the user for a number and returns it once it is validated and in
the range min to max.
*/
int askForNumber(string question, int min, int max) {
	bool quit = false;
	bool isDigitString = true;
	int integer = 0;
	string userInput = "";

	while (!quit) {
		isDigitString = true;
		cout << question;
		getline(cin, userInput);

		for (unsigned int i = 0; i < userInput.length(); i++) {
			if (!isdigit(userInput[i])) {
				isDigitString = false;
			}
		}

		if (isDigitString && userInput.length() > 0) {
			integer = stoi(userInput);

			if (integer >= min && integer <= max) {
				quit = true;
			}

			else {
				cout << "Invalid input!\n";
			}
		}

		else {
			cout << "Invalid input!\n";
		}
	}

	return integer;
}

/*
Asks the user for a letter and once validated returns it.
*/
char askForLetter(string question) {
	string userInput;
	bool quit = false;

	while (!quit) {
		cout << question;
		getline(cin, userInput);

		if (userInput.length() == 1) {
			quit = true;
		}

		else {
			cout << "Invalid input!\n";
		}
	}

	return userInput[0];
}

