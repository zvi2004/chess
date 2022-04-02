#include "Knight.h"

Knight::Knight(const bool isWhite, const int x, const int y, const char type) : Piece(isWhite, x, y, type)
{}
/*
the function check if the move the player want to make is legal
input: destX, destY, isWhite(turn of which color), color of piece
output: num of error or 0 if legal
*/
int Knight::isLegal(int destX, int destY, bool isWhite, bool color)
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
	if ((this->y + 2 == destY && this->x + 1 == destX) || (this->y + 2 == destY && this->x - 1 == destX) || (this->y - 2 == destY && this->x + 1 == destX) || (this->y - 2 == destY && this->x - 1 == destX) || (this->y + 1 == destY && this->x + 2 == destX) || (this->y + 1 == destY && this->x - 2 == destX) || (this->y - 1 == destY && this->x + 2 == destX) || (this->y - 1 == destY && this->x - 2 == destX)) {}//legal move
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
int Knight::nextMoveIndex(Piece* board[][8], int destX, int destY)
{
	if (board[destY][destX]->getColor() == board[this->y][this->x]->getColor() && board[destY][destX]->getType() != '#')//check if dest is not in the same color and clear
	{
		return 3;
	}
	return 0;
}