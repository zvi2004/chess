#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Null.h"
#include <cctype>
#include <string>
#include <iostream>
/*
the function creat the board
input: none
output: none
*/
Board::Board()
{
	//creat white pieces
	this->board[0][0] = new Piece (true, 0, 0, 'R');
	this->board[0][1] = new Piece (true, 1, 0, 'N');
	this->board[0][2] = new Piece (true, 2, 0, 'B');
	this->board[0][3] = new Piece (true, 3, 0, 'K');
	this->board[0][4] = new Piece (true, 4, 0, 'Q');
	this->board[0][5] = new Piece (true, 5, 0, 'B');
	this->board[0][6] = new Piece (true, 6, 0, 'N');
	this->board[0][7] = new Piece (true, 7, 0, 'R');
	//creat black pieces
	this->board[7][0] = new Piece (false, 0, 7, 'r');
	this->board[7][1] = new Piece (false, 1, 7, 'n');
	this->board[7][2] = new Piece (false, 2, 7, 'b');
	this->board[7][3] = new Piece (false, 3, 7, 'k');
	this->board[7][4] = new Piece (false, 4, 7, 'q');
	this->board[7][5] = new Piece (false, 5, 7, 'b');
	this->board[7][6] = new Piece (false, 6, 7, 'n');
	this->board[7][7] = new Piece (false, 7, 7, 'r');

	for (int i = 0; i < 8; i++)//creat pawn on both sides
	{
		this->board[1][i] = new Piece (true, i, 1, 'P');
		this->board[6][i] = new Piece (false, i, 6, 'p');

	}
	for (int i = 2; i < 6; i++)//creat null spaces
	{
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j] = new Piece(false, i, j, '#');
		}
	}
}
/*
the function check if the move the player want to make is lagel make the move according to the answer
input: start x,start y, dest x,dest y, turn of which color
output: error of 0 if legal
*/
int Board::move(int x, int y, int destX, int destY,bool color)
{
	char type = this->board[y][x]->getType(), tempType = ' ';//get type of piece you want to move with
	int error = 0;
	bool tempColor = true;
	tempColor = this->board[destY][destX]->getColor();//get color of dest piece
	tempType = this->board[destY][destX]->getType();//get type of dest piece
	type = tolower(type);
	switch (type)
	{
	case 'k'://if you want to move with king
	{
		King k(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat king
		error = k.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = k.nextMoveIndex(this->board, destX, destY);//check if king can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('K');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('k');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('K');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('k');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					k.~King();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				k.~King();
				return error;
			}
			k.~King();
			return error;
		}
		k.~King();
		return error;
	}

	case 'q'://if you want to move with Queen
	{
		Queen q(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Queen
		error = q.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = q.nextMoveIndex(this->board, destX, destY);//check if Queen can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('Q');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('q');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('Q');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('q');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					q.~Queen();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				q.~Queen();
				return error;
			}
			q.~Queen();
			return error;
		}
		q.~Queen();
		return error;
	}
	case 'r'://if you want to move with Rook
	{
		Rook r(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Rook
		error = r.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = r.nextMoveIndex(this->board, destX, destY);//check if Rook can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('R');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('r');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('R');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('r');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					r.~Rook();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				r.~Rook();
				return error;
			}
			r.~Rook();
			return error;
		}
		r.~Rook();
		return error;
	}
	case 'b'://if you want to move with Bishop
	{
		Bishop b(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Bishop
		error = b.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = b.nextMoveIndex(this->board, destX, destY);//check if Bishop can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('B');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('b');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('B');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('b');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					b.~Bishop();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				b.~Bishop();
				return error;
			}
			b.~Bishop();
			return error;
		}
		b.~Bishop();
		return error;
	}
	case 'n'://if you want to move with Knight
	{
		Knight n(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Knight
		error = n.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = n.nextMoveIndex(this->board, destX, destY);//check if Knight can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('N');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('n');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('N');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('n');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					n.~Knight();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				n.~Knight();
				return error;
			}
			n.~Knight();
			return error;
		}
		n.~Knight();
		return error;
	}
	case 'p'://if you want to move with Pawn
	{
		Pawn p(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Pawn
		error = p.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 0)
		{
			error = p.nextMoveIndex(this->board, destX, destY);//check if Pawn can make the move 
			if (error == 0)
			{
				if (this->board[y][x]->getColor())//if piece is white
				{
					this->board[destY][destX]->setType('P');
					this->board[destY][destX]->setColor(true);
				}
				else//if piece is black
				{
					this->board[destY][destX]->setType('p');
					this->board[destY][destX]->setColor(false);
				}
				//replace old place with null
				this->board[y][x]->setType('#');
				this->board[y][x]->setColor(false);
				error = isCheck(color);//check if there a check
				if (error != 0)//return the board before the move to try and cancel the check
				{
					if (this->board[destY][destX]->getColor())//if white
					{
						this->board[y][x]->setType('P');
						this->board[y][x]->setColor(true);
					}
					else//if black
					{
						this->board[y][x]->setType('p');
						this->board[y][x]->setColor(false);
					}
					this->board[destY][destX]->setType(tempType);
					this->board[destY][destX]->setColor(tempColor);
					p.~Pawn();
					return 4;
				}
				error = isCheck(!color);//check if the move creat check
				p.~Pawn();
				return error;
			}
			p.~Pawn();
			return error;
		}
		p.~Pawn();
		return error;
	}
	case '#'://if you want to move with Null
	{
		Null nu(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Null
		error = nu.isLegal(destX, destY, this->board[y][x]->getColor());//check if move is legal
		return error;
	}
	default:
		break;
	}

}
/*
the function check if the move the player want to make is lagel without changing the board
input: start x,start y, dest x,dest y, turn of which color
output: error of 0 if legal
*/
int Board::checkMove(int x, int y, int destX, int destY, bool color)
{
	char type = this->board[y][x]->getType();
	int error = 0;
	type = tolower(type);
	switch (type)
	{
	case 'k'://if you want to move with King
	{
		King k(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat King
		error = k.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = k.nextMoveIndex(this->board, destX, destY);//check if King can make the move 
			if (error == 0)
			{
				k.~King();
				return 0;
			}
			k.~King();
			return error;
		}
		k.~King();
		return error;
	}
	case 'q'://if you want to move with Queen
	{
		Queen q(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Queen
		error = q.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = q.nextMoveIndex(this->board, destX, destY);//check if Queen can make the move 
			if (error == 0)
			{
				q.~Queen();
				return 0;
			}
			q.~Queen();
			return error;
		}
		q.~Queen();
		return error;
	}
	case 'r'://if you want to move with Rook
	{
		Rook r(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Rook
		error = r.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = r.nextMoveIndex(this->board, destX, destY);//check if Rook can make the move 
			if (error == 0)
			{
				r.~Rook();
				return 0;
			}
			r.~Rook();
			return error;
		}
		r.~Rook();
		return error;
	}
	case 'b'://if you want to move with Bishop
	{
		Bishop b(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Bishop
		error = b.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = b.nextMoveIndex(this->board, destX, destY);//check if Bishop can make the move 
			if (error == 0)
			{
				b.~Bishop();
				return 0;
			}
			b.~Bishop();
			return error;
		}
		b.~Bishop();
		return error;
	}
	case 'n'://if you want to move with Knight
	{
		Knight n(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Knight
		error = n.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = n.nextMoveIndex(this->board, destX, destY);//check if Knight can make the move 
			if (error == 0)
			{
				return 0;
			}
			n.~Knight();
			return error;
		}
		n.~Knight();
		return error;
	}
	case 'p'://if you want to move with Pawn
	{
		Pawn p(this->board[y][x]->getColor(), x, y, this->board[y][x]->getType());//creat Pawn
		error = p.isLegal(destX, destY, this->board[y][x]->getColor(), color);//check if move is legal
		if (error == 2)
		{
			error = p.nextMoveIndex(this->board, destX, destY);//check if Pawn can make the move 
			if (error == 0)
			{
				p.~Pawn();
				return 0;
			}
			p.~Pawn();
			return error;
		}
		p.~Pawn();
		return error;
	}
	default:
		break;
	}

}
/*
the function print the board(only use in terminal)
input: none
output: none
*/
void Board::print()
{
	for (int i = 7; i >=0; i--)
	{
		for (int j = 7; j >= 0; j--)
		{
			std::cout << this->board[i][j]->getType();
		}
		std::cout << std::endl;
	}
}
/*
the function check if theres a check
input: color of current player
output: o if theres no check  adn 1 if theres a check
*/
int Board::isCheck(bool isWhite)
{
	int i = 0, j = 0, kX = 0, kY = 0;
	bool flag = true;
	char type = ' ';
	for (j = 0; j < 8 && flag; j++)//get stats of king
	{
		for (i = 0; i < 8 && flag; i++)
		{
			type = tolower(this->board[j][i]->getType());
			if (type == 'k' && this->board[j][i]->getColor() == isWhite)
			{
				kX = i;
				kY = j;
				flag = false;
			}
		}
	}
	for (i = 0; i < 8; i++)//check if theres a check from rival
	{
		for (j = 0; j < 8; j++)
		{
			if (this->board[j][i]->getColor() == !isWhite && this->board[j][i]->getType() != '#')
			{
				if (checkMove(i, j, kX, kY, isWhite) == 0)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
/*
the function check if the game is over
input: color of player
output: 8 if checkmate 0 if not
*/
int Board::CheckMate(bool isWhite)
{
	int i = 0, j = 0, kX = 0, kY = 0, x = 0, y = 0;
	bool color = true, tempColor = true;
	char type = ' ', tempType = ' ';
	if (isCheck(isWhite))//if theres a check
	{
		for (i = 0; i < 8; i++)//pass every piece on the board
		{
			for (j = 0; j < 8; j++)
			{

				if (this->board[j][i]->getColor() == isWhite && this->board[j][i]->getType() != '#')//if player is the same color
				{
					tempType = this->board[j][i]->getType();//get type
					tempColor = this->board[j][i]->getColor();//get color
					for (x = 0; x < 8; x++)//pass every piece on the board
					{
						for (y = 0; y < 8; y++)
						{
							type = this->board[y][x]->getType();
							color = this->board[y][x]->getColor();
							if (move(i, j, x, y, isWhite) == 0 || move(i, j, x, y, isWhite) == 1)//if the piece move cancel the check
							{
								if (isCheck(isWhite) == 0)//if check removed after the move
								{
									this->board[j][i]->setType(tempType);
									this->board[j][i]->setColor(tempColor);
									this->board[y][x]->setType(type);
									this->board[y][x]->setColor(color);
									return 0;
								}
								this->board[j][i]->setType(tempType);
								this->board[j][i]->setColor(tempColor);
								this->board[y][x]->setType(type);
								this->board[y][x]->setColor(color);
								
							}
						}
					}
				}
			}
		}
	}
	return 8;
}
