#ifndef METAGAMEHPP
#define METAGAMEHPP
#include "metagame.hpp"
#endif


using namespace std;

/* This is the constructor for this class. It initializes the game so that
x has the first move, and initializes the particular board to be used in 
the game. */
Game::Game()
{
	board = new MetaBoard;
	turn = 'X';
}

/* This is the destructor of the class, and it deletes the game board, 
thus freeing the memory allocated to it. */
Game::~Game()
{
	delete board;
}

/* This function is what actually plays the game. The user inputs a row value
and a column value corresponding to where they would like to place their 
symbol. Then the turn changes and it is the other player's turn to make a 
move */
void Game::Run()
{
	int active_board;
	board->Print();
	
	/* This while loop will run until an adequate input is given to select the initial
	active board. */
	while(1)
	{
		cout << "Choose the active board (1 - 9): ";
		cin >> active_board;

		if (ValidMove(active_board) && cin.good())
		{
			break;
		}
		else
		{
			board->Print();
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please select an active board in the range (1 - 9):" << endl;
			continue;
		}
	}

	int new_active;
	int square_choice;
	
	/* This while loop checks to see if the overall game or and individual game has ended,
	either in a win or a draw. It also takes in each player's new move, and will not allow
	them to pick a non-empty square. */
	while (1)
	{
		board->BoardsWon();
		
		/* This handles when an individual board gets full, but it is the active board. 
		A new active board is selected. */
		while(board->FindGame(active_board)->CheckDraw() == 1 && board->CheckDraw()
			!= 1)
		{
			cout << "The active board is full. Please select a new active board (1-9):" << endl;
			cin >> new_active;
			if (!ValidMove(new_active) || !cin.good())
			{
				cout << "That is an invalid board." << endl;
				board->Print();
				cout << "The active board is: " << active_board << endl;
				board->BoardsWon();
				cin.clear();
				cin.ignore(10000, '\n');
				continue;
			}
			else
			{
				active_board = new_active;
				if(board->FindGame(active_board)->CheckDraw() == 1 && board->CheckDraw()
				   != 1)
				{
					board->Print();
					cout << "The active board is: " << active_board << endl;
					board->BoardsWon();
				}
			}
		}

		cout << "It is " << turn << "'s turn. Enter your square (1 - 9): " << endl;
		cin >> square_choice;

		if (!cin.good() || !ValidMove(square_choice))
		{
			board->Print();
			cout << "Please pick a square in the range (1 - 9)" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
			continue;
		}

		if (board->FindGame(active_board)->Query(square_choice - 1) == 'X' 
			|| board->FindGame(active_board)->Query(square_choice - 1) == 'O')
		{
			board->Print();
			cout << "That move has already been made! Pick a new one." << endl;

			continue;
		}

		else
		{
			board->FindGame(active_board)->Place(square_choice - 1, turn);
			// This makes a move for whomever's turn it is.
		}

		board->Print();
		// This prints the board state, note it is after the move has been made
		if (board->FindGame(active_board)->winner != 'X' &&
			board->FindGame(active_board)->winner != 'O')
		{
			if (board->FindGame(active_board)->CheckWin() == 1)
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

					board->FindGame(active_board)->winner = turn;
				
			}
		}

		/* Check to see if the game has been won */
		if (board->CheckWin() == 1)
		{
			cout << "Player " << turn << " wins! (Tic-Tac-Toe, 3 in a row!)" << endl;
			break;
		}

		/* Check to see if the game has ended.*/
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

		active_board = square_choice;

		cout << "The active board is: " << active_board << endl;
		

	}	

}
