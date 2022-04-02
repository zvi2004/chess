#pragma once
#include "Piece.h"
#include "string"
class Board
{
private:
	//fields
	Piece *board[8][8];
public:
	//methods
	Board();//constract board
	~Board() {}; //review: this is the place to delete memory
	int move(int x, int y, int destX, int destY,bool color);//move a piece to new location
	int checkMove(int x, int y, int destX, int destY, bool color);//check if the move in check was legal
	int isCheck(bool isWhite);//check if theres a check
	int CheckMate(bool isWhite);//check if game end
	void print();//print the board
};

