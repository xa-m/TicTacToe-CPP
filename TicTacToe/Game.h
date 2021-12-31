#pragma once
class Game
{
private:


public:
	char table[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

	bool isGameInit = false;
	bool isGameAIopen;
	int moveCount = 0;
	void initGame();

	bool isMoveLegit(int Row, int Colmn);

	void printTable();

	void AIMove();

	
	bool noBlankSpaceLeft();

	bool isGameActive;


	char computerCharacter;
	char playerCharacter;

	// win conditions
	char winner = ' ';
	void WinConditions();

};

