#pragma once
#include "Piece.h"
class Null : protected Piece
{
public:
	//methods
	Null(const bool isWhite, const int x, const int y, const char type);
	~Null() {};
	// this func checks if move was made with null
	int isLegal(int desX, int destY, bool color);
};

