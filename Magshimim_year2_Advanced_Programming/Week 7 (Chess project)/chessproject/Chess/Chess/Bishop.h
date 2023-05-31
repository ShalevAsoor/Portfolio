#pragma once

#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(Side color);
	~Bishop();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

