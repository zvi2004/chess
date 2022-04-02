#include "Pawn.h"
#include <cstdlib>

Pawn::Pawn(const bool isWhite, const int x, const int y, const char type) : Piece(isWhite, x, y, type)
{}
/*
the function check if the move the player want to make is legal
input: destX, destY, isWhite(turn of which color), color of piece
output: num of error or 0 if legal
*/
int Pawn::isLegal(int destX, int destY, bool isWhite, bool color)
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
	if (isWhite)
	{
		if ((this->y == 1 && destY == 3) || (destY - this->y == 1)){}//legal move of white forward
		else
		{
			return 6;
		}
	}
	else
	{
		if ((this->y == 6 && destY == 4) || (this->y - destY == 1)){}//legal move of black forward
		else
		{
			return 6;
		}
	}
	if (abs(this->x - destX) > 1 && abs(this->y - destY) != 2)//legal move to the sides
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
int Pawn::nextMoveIndex(Piece* board[][8], int destX, int destY)
{
	int i = 0, tempX = this->x, tempY = this->y;
	if (abs(this->x - destX) == 1)//check if diagonal move is legal
	{
		
		if (board[destY][destX]->getType() == '#')//check if dest is clear
		{
			return 6;
		}
		if (board[destY][destX]->getColor() == board[this->y][this->x]->getColor())//check if dest is not in the same color
		{
			return 3;
		}
	}
	else//move forward
	{
		if (getColor())//white move forward
		{
			for (i = 0; i < abs(this->y - destY); i++)
			{
				tempY++;
				if (board[tempY][tempX]->getType() != '#')
				{
					return 6;
				}
			}
		}
		else//black move forward
		{
			for (i = 0; i < abs(this->y - destY); i++)
			{
				tempY--;
				if (board[tempY][tempX]->getType() != '#')
				{
					return 6;
				}
			}
		}
	}
	return 0;
}