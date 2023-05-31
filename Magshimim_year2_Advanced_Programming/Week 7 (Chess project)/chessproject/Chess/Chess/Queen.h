#pragma once

#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(Side color);
	~Queen();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

