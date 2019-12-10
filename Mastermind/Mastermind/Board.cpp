/**************************************************
 Author: Jacob Barca
 Purpose: Board Code File
 The Board class' code file
**************************************************/

#include "Board.h"

/*
Default constructor: Initialises the board to easy mode and sets a default
hidden code of 0 0 0 0.
*/
Board::Board() {
	boardColumns = 4;
	boardRows = 10;
	board.push_back(vector<string> {"0", "0", "0", "0"});
	hiddenCode = vector<string>{ "0", "0", "0", "0" };
}

/*
Main constructor: Initialises the values to the given values if they are valid,
if not they are initalised to 0. A hidden row is also added when the board is
created.
*/
Board::Board(int rows, int columns, vector<string> _hiddenCode) {
	if ((columns == 4 && rows == 10 && _hiddenCode.size() == 4) ||
		(columns == 5 && rows == 12 && _hiddenCode.size() == 5) ||
		(columns == 6 && rows == 14 && _hiddenCode.size() == 6)) {
		boardRows = rows;
		boardColumns = columns;
		board.push_back(_hiddenCode);
		hiddenCode = _hiddenCode;
	}

	else {
		boardRows = 0;
		boardColumns = 0;
	}
}

/*
Destructor: not used yet.
*/
Board::~Board() {}

/*
Returns the number of rows that are associated with the board.
*/
int Board::getBoardRows() {
	return boardRows;
}

/*
Returns the number of columns that are associated with the board.
*/
int Board::getBoardColumns() {
	return boardColumns;
}

/*
Returns the number of rows the player has added to the board.
*/
int Board::getCurrentRows() {
	return board.size() - 1;
}

/*
Returns the vector<string> containing the hidden code of the board.
*/
vector<string> Board::getHiddenCode() {
	return hiddenCode;
}

/*
Displays the board in a neatly formatted way given the board vector.
*/
string Board::displayBoard(bool displayHiddenCode) {
	if (board.size() > 0) {
		// hidden row is row 0
		stringstream boardText;
		string boxTop = "";
		string boxMid = "";
		string boxBot = "";
		string clues = "";

		if (!displayHiddenCode)
			createBoxes(boxTop, boxMid, boxBot, vector<string>(boardColumns, " "));
		else
			createBoxes(boxTop, boxMid, boxBot, board[0]);

		boardText << "." << string(5 * boardColumns + 2 * (boardColumns - 1) + 16, '~') << ".\n";
		boardText << "|" << boxTop << "              |\n";
		boardText << "|" << boxMid << " Hidden Code  |\n";
		boardText << "|" << boxBot << "              |\n";
		boardText << "|" << string(5 * boardColumns + 2 * (boardColumns - 1) + 16, '~') << "|\n";

		for (unsigned int i = 1; i < board.size(); i++) {
			clues = "";
			createBoxes(boxTop, boxMid, boxBot, board[i]);

			for (unsigned int j = boardColumns; j < board[i].size(); j++) {
				clues += " " + board[i][j];
			}

			boardText << "|" << boxTop << string(14, ' ') << "|\n";
			boardText << "|" << boxMid << clues << string(14 - (boardColumns * 2), ' ') << "|\n";
			boardText << "|" << boxBot << string(14, ' ') << "|\n";
		}

		boardText << "'" << string(5 * boardColumns + 2 * (boardColumns - 1) + 16, '~') << "'\n";
		return boardText.str();
	}
	else {
		return "";
	}
}

/*
Resets the box string variables equal to new boxes with new values.
*/
void Board::createBoxes(string& boxTop, string& boxMid, string& boxBot, vector<string> values) {
	boxTop = "";
	boxMid = "";
	boxBot = "";

	for (int i = 0; i < boardColumns; i++) {
		boxTop += " .---. ";
		boxMid += " | " + values[i] + " | ";
		boxBot += " '---' ";
	}
}

/*
Adds a new vector<string> row into the board vector.
*/
void Board::createRow(vector<string> playerCode) {
	board.push_back(playerCode);
}

/*
Removes all elements from the board vector rendering it empty.
*/
void Board::resetBoard(vector<string> newHiddenCode) {
	board.clear();
	board.push_back(newHiddenCode);
	hiddenCode = newHiddenCode;
}