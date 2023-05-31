#pragma once
#include <iostream>
#include "Piece.h"

class King : public Piece
{
public:

	King(Side color);
	~King();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

