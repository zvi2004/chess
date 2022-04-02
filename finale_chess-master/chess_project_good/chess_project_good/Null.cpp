#include "Null.h"
#include <cstdlib>

Null::Null(const bool isWhite, const int x, const int y, const char type) : Piece(isWhite, x, y, type)
{}
/*
the function check if the move the player want to make is legal
input: destX, destY, isWhite(turn of which color), color of piece
output: 2
*/
int Null::isLegal(int destX, int destY, bool color)
{
	return 2;
}
