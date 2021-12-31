// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
extern "C" {
#include "Message.h"
}

int main()
{
	Game game;
	int AIModeInput;

	game.initGame();
	WellcomeMessage();


	// initilize loop
	while (!game.isGameInit)
	{
		selectXorO(); // message
		std::cin >> game.playerCharacter;
		selectRandomOrAI(); // message
		std::cin >> AIModeInput;

		if (game.playerCharacter == 'O' || game.playerCharacter == 'o' || game.playerCharacter == 'x' || game.playerCharacter == 'X')
		{
			if (AIModeInput == 0 || AIModeInput == 1)
			{
				// 2 inputs are in their correct form
				// 

				// player symbol input
				if (game.playerCharacter == 'x' || game.playerCharacter == 'X')
				{
					game.computerCharacter = 'O';
					game.playerCharacter = 'X';
				}
				else
				{
					game.computerCharacter = 'X';
					game.playerCharacter = 'O';
				}

				// ai inputs
				if (AIModeInput == 0)
				{
					game.isGameAIopen = false;
				}
				else if (AIModeInput == 1)
				{
					game.isGameAIopen = true;
				}
				game.isGameInit = true;
				break;
			}
		}
		CharNotAcceptable();
	}


	// main game loop
	while (game.isGameActive && !game.noBlankSpaceLeft() && game.isGameInit)
	{
		int playerMoveRow = 0;
		int playerMoveColmn = 0;

		if (game.moveCount == 0 && game.computerCharacter == 'X') { game.AIMove(); }
		game.printTable();
		std::cout << "select where to place " << game.playerCharacter << std::endl << std::endl;

		std::cout << "Row: ";
		std::cin >> playerMoveRow;

		std::cout << "Colmn: ";
		std::cin >> playerMoveColmn;


		if (game.isMoveLegit(playerMoveRow - 1, playerMoveColmn - 1))
		{
			game.table[playerMoveRow - 1][playerMoveColmn - 1] = game.playerCharacter;
			game.moveCount += 1;
			game.WinConditions();
			if (!game.noBlankSpaceLeft() && game.isGameActive)
			{
				game.AIMove();
			}
			else { break; }
		}
		else
		{
			// ai is not gonna make any changes on table
			thisMoveisNotLegit();
		}
	}

	// ending screen
	gameOverMsg();
	game.printTable();


	// win/lose/draw game ending screen

	if (game.winner == game.playerCharacter)
	{
		std::cout << "Winner: " << game.winner << std::endl;
		youWin();
	}
	else if (game.winner == ' ')
	{
		std::cout << "There is no winner." << std::endl;
		itsDraw();
	}
	else
	{
		std::cout << "Winner: " << game.winner << std::endl;
		youLose();
	}

	system("pause");
}