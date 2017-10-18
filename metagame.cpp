#include "metagame.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Game::Game()
/* This is the constructor for this class. It initializes the game so that
x has the first move, and initializes the particular board to be used in 
the game. */
{
	board = new MetaBoard;
	turn = 'X';
}

Game::~Game()
/* This is the destructor of the class, and it deletes the game board, 
thus freeing the memory allocated to it. */
{
	delete board;
}

void Game::Run()
/* This function is what actually plays the game. The user inputs a row value
and a column value corresponding to where they would like to place their 
symbol. Then the turn changes and it is the other player's turn to make a 
move */
{
	int active_board;
	board->Print();
	

	while(1)
	{
		cout << "Choose the active board (1 - 9): ";
		cin >> active_board;

		if (active_board > 1 && active_board < 9)
		{
			break;
		}
		else
		{
			board->Print();
			cout << "Please select an active board in the range (1 - 9):" << endl;
			continue;
		}
	}

	while (1)
	{
		int i;
		int j;

		board->BoardsWon();

		while(board->games[active_board - 1]->CheckDraw() == 1 && board->CheckDraw()
			!= 1)
		{
			cout << "The active board is full. Please select a new active board (1-9):" << endl;
			cin >> j;
			if (j < 1 || j > 9)
			{
				cout << "That is an invalid board." << endl;
				board->Print();
				cout << "The active board is: " << active_board << endl;
				board->BoardsWon();
				continue;
			}
			else
			{
				active_board = j;
				if(board->games[active_board - 1]->CheckDraw() == 1 && board->CheckDraw()
				   != 1)
				{
					board->Print();
					cout << "The active board is: " << active_board << endl;
					board->BoardsWon();
				}
			}
		}

		cout << "It is " << turn << "'s turn. Enter your square (1 - 9): " << endl;
		cin >> i;

		if (i < 1 || i > 9)
		{
			board->Print();
			cout << "Please pick a square in the range (1 - 9)" << endl;

			continue;
		}

		if (board->games[active_board - 1]->Query(i - 1) == 'X' 
			|| board->games[active_board - 1]->Query(i - 1) == 'O')
		{
			board->Print();
			cout << "That move has already been made! Pick a new one." << endl;

			continue;
		}

		else
		{
			board->games[active_board - 1]->Place(i - 1, turn);
			// This makes a move for whomever's turn it is.
		}

		board->Print();
		// This prints the board state, note it is after the move has been made
		if (board->games[active_board - 1]->winner != 'X' &&
			board->games[active_board - 1]->winner != 'O')
		{
			if (board->games[active_board - 1]->CheckWin() == 1)
			{
					cout << "Board number " << active_board << " has been won by: " << turn << endl;
					if (turn == 'X')
					{
						board->xwins++;
					}
					else
					{
						board->owins++;
					}

					board->games[active_board - 1]->winner = turn;
				
			}
		}

		
		if (board->CheckWin() == 1)
		{
			cout << "Player " << turn << " wins! (Tic-Tac-Toe, 3 in a row!)" << endl;
			break;
		}


		if (board->CheckDraw() == 1)
		{
			if(board->xwins > board->owins)
			{
				cout << "Player X wins! (More boards won)" << endl;
				break;
			}
			else if(board->owins > board->xwins)
			{
				cout << "Player O wins! (More boards won)" << endl;
				break;
			}
			else
			{
				cout << "It is a draw. (Same number of boards won)" << endl;
				break;
			}
		}

		// This if statement makes sure the turn changes every time.
		if (turn == 'X')
		{
			turn = 'O';
		}
		else 
		{
			turn = 'X';
		}

		active_board = i;

		cout << "The active board is: " << active_board << endl;
		

	}	

}