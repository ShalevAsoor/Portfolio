#pragma once
#include <iostream>
#include "Piece.h"

class Pawn : public Piece
{
private:

	bool moved;

public:

	Pawn(Side color);
	~Pawn();
	virtual bool MoveCheck(Location src, Location dst, Piece* board_arr[][8]);
	virtual char GetPieceType();
};

