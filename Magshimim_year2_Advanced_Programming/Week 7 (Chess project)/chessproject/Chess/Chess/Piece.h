#pragma once
#include "stdafx.h"
#include "Location.h"

class Piece
{
protected:
	Side _color;

	static bool moveStraight(Location src, Location dst, Piece* board_arr[][8]);
	static bool moveDiagonal(Location src, Location dst, Piece* board_arr[][8]);
public:
	Piece(Side color);
	virtual ~Piece();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]) = 0;
	virtual Side GetColor();
	virtual char GetPieceType() = 0;
};
