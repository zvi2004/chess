#include "Piece.h"
Piece::Piece(const bool isWhite, const int x, const int y, const char type)
{
	this->isWhite = isWhite;
	this->x = x;
	this->y = y;
	this->type = type;
}

char Piece::getType()
{
	return this->type;
}
int Piece::getX()
{
	return this->x;
}
int Piece::getY()
{
	return this->y;
}
bool Piece::getColor()
{
	return this->isWhite;
}
void Piece::setColor(char color)
{
	this->isWhite = color;
}
void Piece::setType(char type)
{
	this->type = type;
}