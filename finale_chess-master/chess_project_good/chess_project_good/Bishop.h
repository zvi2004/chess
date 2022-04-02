#pragma once
#include "Piece.h"
class Bishop : protected Piece
{
public:
	//methods
	Bishop(const bool isWhite, const int x, const int y, const char type);
	~Bishop() {};
	// this func checks if the move made with that figure is legal
	int isLegal(int destX, int destY, bool isWhite, bool color);
	// this fund returns the index of the figure next move
	int nextMoveIndex(Piece *board[][8],int destX, int destY);
};