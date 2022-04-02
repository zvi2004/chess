#pragma once
#include "Piece.h"
class Rook : protected Piece
{
public:
	//methods
	Rook(const bool isWhite, const int x, const int y, const char type);
	~Rook() {};
	// this func checks if the move made with that figure is legal
	int isLegal(int destX, int destY, bool isWhite, bool color);
	// this fund returns the index of the figure next move
	int nextMoveIndex(Piece* board[][8], int destX, int destY);
};