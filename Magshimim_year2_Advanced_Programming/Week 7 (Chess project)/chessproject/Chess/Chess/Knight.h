#pragma once
#include "Piece.h"
class Knight :	public Piece
{
public:
	Knight(Side color);
	~Knight();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

