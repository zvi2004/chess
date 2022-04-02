#pragma once
class Piece
{
protected:
	//fields
	//figure color
	bool isWhite;
	//figure index
	int x;
	int y;
	//figure type: pawn, king...
	char type;

public:
	//methods
	Piece(const bool isWhite, const int x, const int y, const char type);//constractor
	~Piece() {};
	char getType();//return type
	int getX();//return x
	int getY();//return y
	bool getColor();// return color
	void setColor(char color);//change color
	void setType(char type);//change type
};