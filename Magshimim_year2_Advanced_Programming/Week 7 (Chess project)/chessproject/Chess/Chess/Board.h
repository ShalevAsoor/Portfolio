#pragma once
#include "stdafx.h"
#include "Piece.h"
#include "Location.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"	
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"

class Board
{

protected:

	Piece* _board_arr[8][8];
	Side _turn;

public:

	Board(string init_board);
	MoveResult MovePiece(Location src, Location dst);
	bool CheckCheck(Location src, Location dst, Side side);
	Piece* GetPieceType(char p);
	Piece*& operator[](Location loc);
	Location GetKing(Side side);
};
