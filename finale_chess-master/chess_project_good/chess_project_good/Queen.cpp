#include "Queen.h"
#include <cstdlib>

Queen::Queen(const bool isWhite, const int x, const int y, const char type) : Piece(isWhite, x, y, type)
{}
/*
the function check if the move the player want to make is legal
input: destX, destY, isWhite(turn of which color), color of piece
output: num of error or 0 if legal
*/
int Queen::isLegal(int destX, int destY, bool isWhite, bool color)
{
	if (this->x == destX && this->y == destY)//same source and dest
	{
		return 7;
	}
	if (destX <= 7 && destX >= 0 && destY <= 7 && destY >= 0) {}//index inside the board(only in terminal)
	else
	{
		return 5;
	}
	if ((this->x != destX && this->y == destY) || (this->y != destY && this->x == destX) || (abs(this->x - destX) == abs(this->y - destY))) {}//legal move
	else
	{
		return 6;
	}
	if (isWhite != color)//play with color of current player
	{
		return 2;
	}
	return 0;
}
/*
the function check if the piece wont meet another piece on the way
input: board, destX, destY
output: num of error or 0 if legal
*/
int Queen::nextMoveIndex(Piece* board[][8], int destX, int destY)
{
	int i = 0, tempX = this->x, tempY = this->y;
	if (board[destY][destX]->getColor() == board[this->y][this->x]->getColor() && board[destY][destX]->getType() != '#')//check if dest is not in the same color and clear
	{
		return 3;
	}
	if (this->x == destX && this->y < destY)//check if going up is clear
	{
		for (i = 0; i < abs(this->y - destY) - 1; i++)
		{
			tempY++;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x < destX && this->y == destY)//check if going right is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX++;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x == destX && this->y > destY)//check if going down is clear
	{
		for (i = 0; i < abs(this->y - destY) - 1; i++)
		{
			tempY--;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x > destX && this->y == destY)//check if going left is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX--;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x < destX && this->y < destY)//check if going up right is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX++;
			tempY++;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x < destX && this->y > destY)//check if going down right is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX++;
			tempY--;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x > destX && this->y > destY)//check if going down left is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX--;
			tempY--;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	else if (this->x > destX && this->y < destY)//check if going up left is clear
	{
		for (i = 0; i < abs(this->x - destX) - 1; i++)
		{
			tempX--;
			tempY++;
			if (board[tempY][tempX]->getType() != '#')
			{
				return 6;
			}
		}
	}
	return 0;
}