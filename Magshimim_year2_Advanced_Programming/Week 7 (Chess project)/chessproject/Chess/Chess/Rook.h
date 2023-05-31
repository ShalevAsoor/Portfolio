#pragma once

#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(Side color);
	~Rook();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

