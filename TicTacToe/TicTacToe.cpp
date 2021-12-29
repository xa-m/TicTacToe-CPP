// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main()
{
	Game game;

	game.initGame();
	std::cout << "Wellcome to BasicTicTacToe\n";

	// initilize loop
	while (!game.isGameInit)
	{
		std::cout << "Select X or O by typing X or O" << std::endl;
		std::cin >> game.playerCharacter;

		if (game.playerCharacter == 'O' || game.playerCharacter == 'o' || game.playerCharacter == 'x' || game.playerCharacter == 'X')
		{
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
			game.isGameInit = true;
			break;
		}
		std::cout << "This char is not acceptable... try again." << std::endl;
	}


	// main game loop
	while (game.isGameActive && !game.isGameEnd() && game.isGameInit)
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
			if (!game.isGameEnd() && game.isGameActive)
			{
				game.AIMove();
			}
			else { break; }
		}
		else
		{
			// ai is not gonna make any changes on table
			std::cout << "This move is not legit, try another move.\n";
		}
	}

	// ending screen
	std::cout << "Game Over, that the final table of this game:" << std::endl;
	game.printTable();


	// win/lose/draw game ending screen

	if (game.winner == game.playerCharacter)
	{
		std::cout << "Winner: " << game.winner << std::endl;
		std::cout << "Congratulations! You win!" << std::endl;
	}
	else if (game.winner == ' ')
	{
		std::cout << "There is no winner." << std::endl;
		std::cout << "HMM, That looks like draw to me. Maybe another time..." << std::endl;
	}
	else
	{
		std::cout << "Winner: " << game.winner << std::endl;
		std::cout << "Ow, You Looks like you lose. :( maybe another time..." << std::endl;
	}

}