/* This class holds the game state. It manages the current state of the board
and which player's turn it is. */
#include "metaboard.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


class Game
{
private: /* These member variables are an instance of the MyBoard class
for the board and the person who's turn it is. */
	MetaBoard *board;
	char turn;
public:
	Game();
	~Game();
	void Print();
	void Run();
};