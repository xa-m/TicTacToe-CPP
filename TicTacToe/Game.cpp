#include "Game.h"
#include <iostream>
#include <ctime>

void Game::initGame()
{
	isGameActive = true;
}

bool Game::isMoveLegit(int Row, int Colmn)
{
	if (Colmn + 1 > 3 && Colmn + 1 < 1 && Row + 1 > 3 && Row + 1 < 1) { return false; }

	char mark = table[Row][Colmn];

	if (mark != ' ') { return false; }

	if (!isGameActive) { return false; }

	return true;
}


void Game::printTable()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << "|" << " " << table[i][0] << " " << "|" << " " << table[i][1] << " " << "|" " " << table[i][2] << " " << "|" << std::endl << std::endl;
	}
}

void Game::AIMove()
{
	// after ai move it needs to check WinConditions(), and increase moveCount by 1.

	// if game ai is closed.
	if (!isGameAIopen)
	{
		srand(time(0));
		while (true)
		{
			int Row = rand() % 3;
			int Colmn = rand() % 3;
			if (isMoveLegit(Row, Colmn))
			{
				table[Row][Colmn] = computerCharacter;
				moveCount += 1;
				WinConditions();
				break;
			}
		}
		return;
	}

	// if game ai is working...
	// game ai section


	if (computerCharacter == 'X')
	{
		// first move
		if (moveCount == 0)
		{
			table[2][2] = computerCharacter;
			moveCount++;
		}

		if (moveCount == 2)
		{
			if (table[1][1] != 'O')
			{
				XGameStarsWithCenter = false;
				// win condiiton
				if (table[2][1] == 'O' || table[2][0] == 'O')
				{
					table[0][2] = computerCharacter;
					moveCount++;
				}
				else
				{
					table[2][0] = computerCharacter;
					moveCount++;
				}

				// old algorithm
				/*else if (table[0][2] == 'O' || table[1][2] == 'O')
				{
					table[2][0] = computerCharacter;
					moveCount++;
				}*/
			}
			else
			{
				// enemy places O to center.
				XGameStarsWithCenter = true;
				table[0][0] = computerCharacter;
				moveCount++;
			}
		}

		if (moveCount == 4 && !XGameStarsWithCenter)
		{
			if (table[0][2] == computerCharacter && table[1][2] == ' ')
			{
				table[1][2] = computerCharacter;
				moveCount++;
			}
			else if (table[0][2] == computerCharacter && table[1][2] == playerCharacter)
			{
				if (table[0][0] == ' ')
				{
					table[0][0] = computerCharacter;
					moveCount++;
				}
				else if (table[2][0] == ' ')
				{
					table[2][0] = computerCharacter;
					moveCount++;
				}
			}


			if (table[2][0] == computerCharacter && table[2][1] == ' ')
			{
				table[2][1] = computerCharacter;
				moveCount++;
			}
			else if (table[2][0] == computerCharacter && table[2][1] == playerCharacter)
			{
				if (table[0][2] == ' ')
				{
					table[0][2] = computerCharacter;
					moveCount++;
				}
				else if (table[0][0] == ' ')
				{
					table[0][0] = computerCharacter;
					moveCount++;
				}
			}
		}


		// 'O' centered.
		if (moveCount == 4 && XGameStarsWithCenter)
		{
			// win condition
			if (table[0][2] == playerCharacter && table[2][0] == ' ')
			{
				table[2][0] = computerCharacter;
				moveCount++;
			}
			else if (table[2][0] == playerCharacter && table[0][2] == ' ')
			{
				table[0][2] = computerCharacter;
				moveCount++;
			}

			// Tie condition
			if (table[0][1] == playerCharacter)
			{
				table[2][1] = computerCharacter;
				moveCount++;
			}
			else if (table[1][2] == playerCharacter)
			{
				table[1][0] = computerCharacter;
				moveCount++;
			}
			else if (table[1][0] == playerCharacter)
			{
				table[1][2] = computerCharacter;
				moveCount++;
			}
			else if (table[2][1] == playerCharacter)
			{
				table[0][1] = computerCharacter;
				moveCount++;
			}
		}

		// regular game condition
		if (moveCount == 6 && !XGameStarsWithCenter)
		{
			if (table[0][0] == computerCharacter && table[2][2] == computerCharacter && table[1][1] == ' ')
			{
				table[1][1] = computerCharacter;
				moveCount++;
			}
			else if (table[0][2] == computerCharacter && table[2][0] == computerCharacter && table[1][1] == ' ')
			{
				table[1][1] = computerCharacter;
				moveCount++;
			}

			if (table[2][0] == computerCharacter && table[2][1] == ' ')
			{
				table[2][1] = computerCharacter;
				moveCount++;
			}
			else if (table[2][0] == computerCharacter && table[2][1] == playerCharacter)
			{
				if (table[0][2] == ' ')
				{
					table[0][2] = computerCharacter;
					moveCount++;
				}
				else if (table[0][0] == ' ')
				{
					table[0][0] = computerCharacter;
					moveCount++;
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (table[i][0] == computerCharacter && table[i][2] == computerCharacter && table[i][1] == ' ')
				{
					table[i][1] = computerCharacter;
					moveCount++;
				}
				if (table[0][i] == computerCharacter && table[2][i] == computerCharacter && table[1][i] == ' ')
				{
					table[1][i] = computerCharacter;
					moveCount++;
				}
			}
		}


		if (moveCount == 6 && XGameStarsWithCenter)
		{
			// win condition
			if (table[2][0] == computerCharacter || table[0][2] == computerCharacter)
			{
				if (table[2][0] == computerCharacter)
				{
					if (table[1][0] == ' ')
					{
						table[1][0] = computerCharacter;
						moveCount++;
					}
					else if (table[2][1] == ' ')
					{
						table[2][1] = computerCharacter;
						moveCount++;
					}
				}
				else if (table[0][2] == computerCharacter)
				{
					if (table[0][1] == ' ')
					{
						table[0][1] = computerCharacter;
						moveCount++;
					}
					else if (table[1][2] == ' ')
					{
						table[1][2] = computerCharacter;
						moveCount++;
					}
				}
				else
				{
					for (int i = 0; i < 3; i++)
					{
						if (table[i][0] == computerCharacter && table[i][2] == computerCharacter && table[i][1] == ' ')
						{
							table[i][1] = computerCharacter;
							moveCount++;
						}
						else if (table[0][i] == computerCharacter && table[2][i] == computerCharacter && table[1][i] == ' ')
						{
							table[1][i] = computerCharacter;
							moveCount++;
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					if (table[i][0] == computerCharacter && table[i][2] == computerCharacter && table[i][1] == ' ')
					{
						table[i][1] = computerCharacter;
						moveCount++;
					}
					else if (table[0][i] == computerCharacter && table[2][i] == computerCharacter && table[1][i] == ' ')
					{
						table[1][i] = computerCharacter;
						moveCount++;
					}
				}
			}
		}

	}
	else if (computerCharacter == 'O')
	{

	}

	// checks win conditions
	WinConditions();
}

void Game::WinConditions()
{
	for (int i = 0; i < 3; i++)
	{
		// win condition 1

		//	| X |   |   |
		// 
		//	| X |   |   |
		// 
		//	| X |   |   |

		if (table[0][i] == 'X' && table[1][i] == 'X' && table[2][i] == 'X')
		{
			winner = 'X';
			isGameActive = false;
		}
		else if (table[0][i] == 'O' && table[1][i] == 'O' && table[2][i] == 'O')
		{
			winner = 'O';
			isGameActive = false;
		}

		// win condition 2

		//	| X | X | X |
		// 
		//	|   |   |   |
		// 
		//	|   |   |   |

		if (table[i][0] == 'X' && table[i][1] == 'X' && table[i][2] == 'X')
		{
			winner = 'X';
			isGameActive = false;
		}
		else if (table[i][0] == 'O' && table[i][1] == 'O' && table[i][2] == 'O')
		{
			winner = 'O';
			isGameActive = false;
		}

	}

	// win condition 3 / 1

	//	| X |   |   |
	// 
	//	|   | X |   |
	// 
	//	|   |   | X |

	if (table[0][0] == 'X' && table[1][1] == 'X' && table[2][2] == 'X')
	{
		winner = 'X';
		isGameActive = false;
	}
	else if (table[0][0] == 'O' && table[1][1] == 'O' && table[2][2] == 'O')
	{
		winner = 'O';
		isGameActive = false;
	}

	// win condition 3 / 2

	//	|   |   | X |
	// 
	//	|   | X |   |
	// 
	//	| X |   |   |

	if (table[0][2] == 'X' && table[1][1] == 'X' && table[2][0] == 'X')
	{
		winner = 'X';
		isGameActive = false;
	}
	else if (table[0][2] == 'O' && table[1][1] == 'O' && table[2][0] == 'O')
	{
		winner = 'O';
		isGameActive = false;
	}

	if (noBlankSpaceLeft() && winner == ' ')
	{
		winner = ' ';
		isGameActive = false;
	}

}

bool Game::noBlankSpaceLeft()
{

	int blankSpace = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int q = 0; q < 3; q++)
		{
			if (table[i][q] == ' ')
			{
				blankSpace++;
			}
		}
	}

	return blankSpace == 0 ? true : false;
}

//		| X |   |   |
// 
//		| X | O |   |
// 
//		|   |   |   |

