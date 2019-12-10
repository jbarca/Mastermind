/**************************************************
 Author: Jacob Barca
 Purpose: Board Header File
 The Board class' header file
**************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Board {
public:
	// constructors
	Board();
	Board(int rows, int columns, vector<string> hiddenCode);

	// destructors
	~Board();

	// accessors
	int getBoardRows();
	int getBoardColumns();
	int getCurrentRows();
	vector<string> getHiddenCode();
	string displayBoard(bool displayHiddenCode = false);

	// mutators and quasi-mutators
	void createRow(vector<string> playerCode);
	void resetBoard(vector<string> newHiddenCode);


private:
	// private instance variables and functions
	void createBoxes(string& boxTop, string& boxMid, string& boxBot, vector<string> values);

	int boardRows;
	int boardColumns;
	vector<string> hiddenCode;
	vector<vector<string>> board;
};

#endif

