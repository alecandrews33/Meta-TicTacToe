#include "metaboard.hpp"
#include <iostream>

using namespace std;

MyBoard::MyBoard()
/* This is the constructor for the MyBoard class, which establishes a board
that is full of unnocupied spaces */
{
	for (int x = 0; x < 9; x++)
	{
		squares[x] = ' '; // The board array is filled with spaces
							 // since that means it is unoccupied.
	}
}

MyBoard::~MyBoard()
/* The deconstructor wasn't used since dynamic memory allocation wasn't
utilized and thus there was no memory that needed to be deleted. */
{

}

char MyBoard::Query(int x)
/* This function returns the value stored in a certain box in the board.
It takes x and y coordinates as arguments. */
{
	return squares[x];
}

void MyBoard::Place(int square, char piece)
/* This function makes a move on the board, placing the given piece
in the given box. It takes the square and the piece that is 
making the move as its arguments. It returns void. */
{
	squares[square] = piece;
}

int MyBoard::CheckWin()
/* This function checks to see if a player has won the game. It takes no 
arguments and returns 1 for a win and 0 for no win. */
{
	for (int x = 0; x < 3; x++)
	{
		// Check for a horizontal win
		if (squares[3 * x] != ' ' && squares[3 * x + 1] != ' ' && squares[3 * x + 2] != ' ')
		{
			if (squares[3 * x] == squares[3 * x + 1] && squares[3 * x + 1] == squares[3 * x + 2])
			{
				winner = squares[3 * x];
				return 1;
			}
		}

		// Check for a vertical win
		if (squares[x] != ' ' && squares[x + 3] != ' ' && squares[x + 6] != ' ')
		{
			if (squares[x] == squares[x + 3] && squares [x + 3] ==
				squares[x + 6]) 
			{
				winner = squares[x];
				return 1;
			}

		}

	}


	// Check for a diagonal win from top left to bottom right
	if (squares[0] != ' ')
	{
		if (squares[0] == squares[4] && squares[4] ==
			squares[8]) 
		{
			winner = squares[0];
			return 1;
		}

	}

	// Check for a diagonal win from top right to bottom left
	if (squares[2] != ' ')
	{
		if (squares[2] == squares[4] && squares[4] ==
			squares[6])
		{
			winner = squares[2];
			return 1;
		}

	}

	return 0;

}

int MyBoard::CheckDraw()
/* This function checks to see if the game has ended in a draw. It returns
1 if it is a draw and 0 if it is not. */
{
	for (int x = 0; x < 9; x++)
	{
		if (squares[x] == ' ')
		return 0;
	}
	return 1;
}

void MyBoard::Print()
/* This function prints the current state of the board to the terminal. 
It takes no arguments as it can access the board through the member
variable. */
{	
	for (int x = 0; x < 3; x++)
	{
		cout << ' ';
		cout << squares[3 * x];

		cout << " | ";

		cout << squares[3 * x + 1];

		cout << " | ";

		cout << squares[3 * x + 2] << endl;

		if (x != 2)
		{
			cout << "-----------" << endl;
		}
	}
	
}

MetaBoard::MetaBoard()
{
	/* Establish the 9 individual boards that make up the metaboard. */
	for (int x = 0; x < 9; x++)
	{
		games[x] = new MyBoard;
	}
}

MetaBoard::~MetaBoard()
{
	/* Delete each of the 9 individual games. */
	for (int x = 0; x < 9; x++)
	{
		delete games[x]; 
	}
}

int MetaBoard::CheckWin()
{
	
	for (int x = 0; x < 3; x++)
	{
		// Check for a horizontal win
		if ((games[3 * x]->winner == games[3 * x + 1]->winner && games[3 * x + 1]->winner
		 == games[3 * x + 2]->winner) && (games[3 * x]->winner == 'X' 
		 	|| games[3 * x]->winner == 'O') )
		{
			if (games[3 * x]->winner == 'X')
			{
				xwins++;
			}
			else
			{
				owins++;
			}
			return 1;
		}


		// Check for a vertical win
		if ((games[x]->winner == games[x + 3]->winner && games[x + 3]->winner == games[x + 6]->winner) &&
			(games[x]->winner == 'X' || games[x]->winner == 'O'))
		{
			if (games[3 * x]->winner == 'X')
			{
				xwins++;
			}
			else
			{
				owins++;
			}
			return 1;
		}
	}
	
	// Check for a diagonal win from top left to bottom right
	if (games[0]->winner == 'X' || games[0]->winner == 'O')
	{
		if ((games[0]->winner == games[4]->winner) && (games[4]->winner ==
			games[8]->winner))
		{
			if (games[0]->winner == 'X')
			{
				xwins++;
			}
			else
			{
				owins++;
			}
			return 1;
		}

	}

	// Check for a diagonal win from top right to bottom left
	if (games[2]->winner == 'X' || games[2]->winner == 'O')
	{
		if ((games[2]->winner == games[4]->winner) && (games[4]->winner == games[6]->winner))
		{
			if (games[2]->winner == 'X')
			{
				xwins++;
			}
			else
			{
				owins++;
			}
			return 1;
		}
	}

	return 0;
}

int MetaBoard::CheckDraw()
{
	/* A draw would only occur if no moves were available. Check 
	all of the games on the board and see if any have available moves. */
	for (int x = 0; x < 9; x++)
	{
		if (games[x]->CheckDraw() == 0)
		{
			return 0;
		}
	}
	return 1;
}

void MetaBoard::BoardsWon()
{
	/* This function checks and prints to the console which boards 
	each team has already won. This will be called to keep the players
	updated on which boards they have won. */
	int winner = 0;
	int xwin = 0;
	int owin = 0;

	for (int x = 0; x < 9; x++)
	{
		if (games[x]->winner == 'X' ||
			games[x]->winner == 'O')
		{
			winner = 1;
		}
	}

	// If a board has been won, print to the console this information
	if(winner == 1)
	{

	cout << "X has won the following boards: ";

	for (int x = 0; x < 9; x++)
	{
		if (games[x]->winner == 'X')
		{
			xwin = 1;
			cout << (x + 1) << " ";
		}
	}

	if (xwin != 1)
	{
		cout << "(None) ";
	}

	cout << "|| O has won the following boards: ";

	for (int x = 0; x < 9; x++)
	{
		if (games[x]->winner == 'O')
		{
			cout << (x + 1) << " ";
			owin = 1;
		}
	}

	if (owin != 1)
	{
		cout << "(None)";
	}

	cout << endl;
	}

	// Otherwise, print that no one has won a board.
	else
	{
		cout << "No one has won a board!" << endl;
	}
}

void MetaBoard::Print()
{
	/* This function prints out the metaboard to the console in 
	a user friendly manner. */	
	cout << " " << games[0]->Query(0) << " | " << games[0]->Query(1) << " | " << games[0]->Query(2)
	<< " | " << games[1]->Query(0) << " | " << games[1]->Query(1) << " | " << games[1]->Query(2)
	<< " | " << games[2]->Query(0) << " | " << games[2]->Query(1) << " | " << games[2]->Query(2) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[0]->Query(3) << " | " << games[0]->Query(4) << " | " << games[0]->Query(5)
	<< " | " << games[1]->Query(3) << " | " << games[1]->Query(4) << " | " << games[1]->Query(5)
	<< " | " << games[2]->Query(3) << " | " << games[2]->Query(4) << " | " << games[2]->Query(5) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[0]->Query(6) << " | " << games[0]->Query(7) << " | " << games[0]->Query(8)
	<< " | " << games[1]->Query(6) << " | " << games[1]->Query(7) << " | " << games[1]->Query(8)
	<< " | " << games[2]->Query(6) << " | " << games[2]->Query(7) << " | " << games[2]->Query(8) << endl;

	cout << "___________________________________" << endl << endl;

	cout << " " << games[3]->Query(0) << " | " << games[3]->Query(1) << " | " << games[3]->Query(2)
	<< " | " << games[4]->Query(0) << " | " << games[4]->Query(1) << " | " << games[4]->Query(2)
	<< " | " << games[5]->Query(0) << " | " << games[5]->Query(1) << " | " << games[5]->Query(2) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[3]->Query(3) << " | " << games[3]->Query(4) << " | " << games[3]->Query(5)
	<< " | " << games[4]->Query(3) << " | " << games[4]->Query(4) << " | " << games[4]->Query(5)
	<< " | " << games[5]->Query(3) << " | " << games[5]->Query(4) << " | " << games[5]->Query(5) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[3]->Query(6) << " | " << games[3]->Query(7) << " | " << games[3]->Query(8)
	<< " | " << games[4]->Query(6) << " | " << games[4]->Query(7) << " | " << games[4]->Query(8)
	<< " | " << games[5]->Query(6) << " | " << games[5]->Query(7) << " | " << games[5]->Query(8) << endl;

	cout << "___________________________________" << endl << endl;
	
	cout << " " << games[6]->Query(0) << " | " << games[6]->Query(1) << " | " << games[6]->Query(2)
	<< " | " << games[7]->Query(0) << " | " << games[7]->Query(1) << " | " << games[7]->Query(2)
	<< " | " << games[8]->Query(0) << " | " << games[8]->Query(1) << " | " << games[8]->Query(2) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[6]->Query(3) << " | " << games[6]->Query(4) << " | " << games[6]->Query(5)
	<< " | " << games[7]->Query(3) << " | " << games[7]->Query(4) << " | " << games[7]->Query(5)
	<< " | " << games[8]->Query(3) << " | " << games[8]->Query(4) << " | " << games[8]->Query(5) << endl;

	cout << "---------- | --------- | ----------" << endl;

	cout << " " << games[6]->Query(6) << " | " << games[6]->Query(7) << " | " << games[6]->Query(8)
	<< " | " << games[7]->Query(6) << " | " << games[7]->Query(7) << " | " << games[7]->Query(8)
	<< " | " << games[8]->Query(6) << " | " << games[8]->Query(7) << " | " << games[8]->Query(8) << endl;
}

MyBoard * MetaBoard::FindGame(int x)
{
	return games[x - 1]
}

