/* This class sets up an eligible Tic-Tac-Toe board to be used when the game
is run. */
class MyBoard
{
private:
	/* This member variable establishes the board */
	char squares[9];
public:
	char winner;
	char Query(int x);
	void Place(int x, char piece);
	int CheckWin();
	int CheckDraw();
	void Print();
	~MyBoard();
	MyBoard();
};

class MetaBoard
{
private:
public:
	int xwins = 0;
	int owins = 0;
	MyBoard * games[9];
	int CheckWin();
	int CheckDraw();
	void Print();
	void BoardsWon();
	~MetaBoard();
	MetaBoard();
};
