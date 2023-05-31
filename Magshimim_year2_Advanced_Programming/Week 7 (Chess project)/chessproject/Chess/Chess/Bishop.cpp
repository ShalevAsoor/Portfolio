#include "Bishop.h"

//ctor
Bishop::Bishop(Side color): Piece(color) {}

//dtor
Bishop::~Bishop() {}

/*
this function is checking if the move of the bishop is valid
Input:  its src, dst, and the board
Output: if the move is valid
*/
bool Bishop::MoveCheck(Location src, Location dst, Piece * board_arr[][8])
{
	return Piece::moveDiagonal(src, dst, board_arr);
}

//getter
char Bishop::GetPieceType()
{
	return 'b';
}
