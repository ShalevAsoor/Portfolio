#include "Rook.h"

//ctor
Rook::Rook(Side color): Piece(color) {}

//dtor
Rook::~Rook() {}


bool Rook::MoveCheck(Location src, Location dst, Piece* board_arr[][8])
{
	return Piece::moveStraight(src, dst, board_arr);
}

//getter
char Rook::GetPieceType()
{
	return 'r';
}
