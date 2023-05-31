#include "Knight.h"

Knight::Knight(Side color): Piece(color) {}


Knight::~Knight() {}

/*
this function is checking if the move of the knight is valid
Input:  its src, dst, and the board
Output: if the move is valid
*/
bool Knight::MoveCheck(Location src, Location dst, Piece * board_arr[][8])
{
	int verctical_diff = dst.GetRow() - src.GetRow();					  //row desired move
	int horizontal_diff = dst.GetCol() - src.GetCol();				 //col desired move
	return abs(horizontal_diff) == 2 && abs(verctical_diff) == 1 ||		//check if src and dst are a legal Knight move
		   abs(horizontal_diff) == 1 && abs(verctical_diff) == 2;
}

//getter
char Knight::GetPieceType()
{
	return 'n';
}
