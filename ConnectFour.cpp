#include <iostream>
#include <string>
#include <sstream>
#include <ctype.h>
using namespace std;
int rowcount, colcount;
int **chessBoard= nullptr;
int *column;

//int chessboard[6][7];
//int column[7];
int fullcolumn = 0;
enum chesstype { black, white };
bool hasWinner = false;
int _condition = 0;

class Player {
private:
	chesstype type;
public:
	inline chesstype gettype() { return type; }
	inline void settype(chesstype _type) { type = _type;}
};

Player p1, p2;

bool CheckHorzitonal(int x, int y);
bool CheckVertical(int x, int y);
bool Check45degree(int x, int y);
bool Check135degree(int x, int y);

bool CheckWin(int x, int y)
{
	bool win = false;
	win = CheckHorzitonal(x, y);
	if (!win)
		win = CheckVertical(x, y);
	if (!win)
		win = Check45degree(x, y);
	if (!win)
		win = Check135degree(x, y);

	return win;
}

bool CheckHorzitonal(int x, int y)
{
	int count = 0;
	for(int i = 0; i < _condition;++i)
	{
		if (chessBoard[x][y] == chessBoard[x][(y + i) % colcount])
		{
			++count;
		}
		else
			break;
	}

	if (count == _condition)
		return true;

	for(int i = 1; i < _condition; ++i)
	{
		if(y - i < 0)
		{
			if (chessBoard[x][y] == chessBoard[x][y - i + colcount])
				++count;
			else break;
		}
		else
		{
			if (chessBoard[x][y] == chessBoard[x][y - i])
				++count;
			else break;
		}
	}

	if (count == _condition)
		return true;
	else
		return false;
}

bool CheckVertical(int x, int y)
{
	int count = 0;
	for (int i = 0; i < _condition; ++i)
	{
		if (chessBoard[x][y] == chessBoard[(x + i) % rowcount][y])
		{
			++count;
		}
		else
			break;
	}

	if (count == _condition)
		return true;

	for (int i = 1; i < _condition; ++i)
	{
		if (x - i < 0)
		{
			if (chessBoard[x][y] == chessBoard[x - i + rowcount][y])
				++count;
			else break;
		}
		else
		{
			if (chessBoard[x][y] == chessBoard[x - i][y])
				++count;
			else break;
		}
	}

	if (count == _condition)
		return true;
	else
		return false;
}

bool Check45degree(int x, int y)
{
	int count = 0;
	for(int i = 0; i < _condition; ++i)
	{
		if ((x - i) >= 0 && (y + i) < colcount && chessBoard[x][y] == chessBoard[x - i][y + i])
			++count;
		else break;
	}
	
	if (count == _condition)
		return true;

	for(int i = 1; i < _condition; ++i)
	{
		if ((x + i) < rowcount && (y - i) >= 0 && chessBoard[x][y] == chessBoard[x + i][y - i])
			++count;
		else break;
	}
	if (count == _condition)
		return true;
	return false;
}

bool Check135degree(int x, int y)
{
	int count = 0;
	for (int i = 0; i < _condition; ++i)
	{
		if ((x + i) < rowcount && (y + i) < colcount && chessBoard[x][y] == chessBoard[x + i][y + i])
			++count;
		else break;
	}
	if (count == _condition)
		return true;

	for (int i = 1; i < _condition; ++i)
	{
		if ((x - i) >= 0 && (y - i) >= 0 && chessBoard[x][y] == chessBoard[x - i][y - i])
			++count;
		else break;
	}
	if (count == _condition)
		return true;
	return false;
}

void Init();
void show();
void Update(int, int , chesstype);
int findtoInsert(int column);


void Init()
{
	chessBoard = new int*[rowcount];
	for (int i = 0; i < rowcount; i++)
		chessBoard[i] = new int[colcount];
	column = new int[colcount];
	for (int i = 0; i < colcount; i++)
		column[i] = i;
	for(int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < colcount; j++)
			chessBoard[i][j] = -1;
	}
	p1.settype(black);
	p2.settype(white);
}

void show()
{
	for (int i = 0; i < colcount; i++)
		cout << column[i] << "  ";
	cout << endl;
	for (int i = 0; i < rowcount; ++i)
	{
		for (int j = 0; j < colcount; ++j)
		{
			cout << chessBoard[i][j] << " ";
		}
		cout << endl;
	}
}

void GetInput(Player p){
	bool success = false;
	char ccolumn;
	int col = 0;
	int row = 0;
	if(p.gettype() == p1.gettype())
	{
		while(!success)
		{
			cout << "Player1's Turn! Type the column number to insert a piece"
				<< endl;
			cin >> col;
			if(col >= colcount || col < 0)
			{
				cout << "this is not a valid column number, please try a valid number(0-6)"
					<< endl;
				success = false;
			}
			else
			{
				row = findtoInsert(col);
				if(row == -1)
				{
					cout << "this column is full, please try another" << endl;
					++fullcolumn;
					success = false;
				}
				else
				{
					success = true;
				}
			}
		}
		Update(row, col, p1.gettype());
	}
	else
	{
		while (!success)
		{
			cout << "Player2's Turn! Type the column number to insert a piece"
				<< endl;
			cin >> col;
			if (col >= colcount || col < 0)
			{
				cout << "this is not a valid column number, please try a valid number(0-6)"
					<< endl;
				success = false;
			}
			else
			{
				row = findtoInsert(col);
				if (row == -1)
				{
					cout << "this column is full, please try another" << endl;
					++fullcolumn;
					success = false;
				}
				else
				{
					success = true;
				}
			}
		}
		Update(row, col, p2.gettype());
	}
}

int findtoInsert(int column)
{
	int row = -1;
	for(int i = rowcount - 1; i >= 0; i--)
	{
		if (chessBoard[i][column] == -1)
		{
			row = i;
			break;
		}
	}
	return row;
}

void Update(int row, int column, chesstype chess)
{
	if(chess == p1.gettype())
	{
		chessBoard[row][column] = p1.gettype();
	}
	else if(chess == p2.gettype())
	{
		chessBoard[row][column] = p2.gettype();
	}
	show();
	if (CheckWin(row, column))
	{
		hasWinner = true;
		if (chessBoard[row][column] == p1.gettype())
			cout << "P1 is the winner! Congratulations!" << endl;
		else if (chessBoard[row][column] == p2.gettype())
			cout << "P2 is the winner! Congratulations!" << endl;
	}
	
}

int main()
{
	bool inrange = true;
	bool restart = false;
	do 
	{
		hasWinner = false;
		do 
		{
			cout << "win condition: " << endl;
			cin >> _condition;
			if(_condition > 20 || _condition < 3)
			{
				inrange = false;
			}
			else
				inrange = true;
		} while (!inrange); // in range condition

		do
		{
			cout << "chess row: " << endl;
			cin >> rowcount;
			if (rowcount > 20 || rowcount < 4)
			{
				inrange = false;
			}
			else
				inrange = true;
		} while (!inrange); // in range rowcount
		do
		{
			cout << "chess col: " << endl;
			cin >> colcount;
			if (colcount > 20 || colcount < 4)
			{
				inrange = false;
			}
			else
				inrange = true;
		} while (!inrange); // in range colcount
		cout << " Let's play Connect Four! " << endl;
		Init();
		show();
		while (1)
		{
			GetInput(p1);
			if (fullcolumn == colcount)
			{
				cout << "this is a draw!" << endl;
				break;
			}
			if (hasWinner)
				break;
			
			GetInput(p2);
			if (fullcolumn == colcount)
			{
				cout << "this is a draw!" << endl;
				break;
			}
			if (hasWinner)
				break;
		}
		cout << "do you want to play another round?(y for yes, other key for no)" << endl;
		char choose;
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			restart = true;
		}
		else
		{
			restart = false;
		}
	} while (restart);
	system("pause");
	return 0;
}