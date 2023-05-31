#include "King.h"

//ctor
King::King(Side color): Piece(color) {}

//dtro
King::~King() {}

//this function check if the king move is valid
bool King::MoveCheck(Location src, Location dst, Piece * board_arr[][8])
{
	int verctical_diff = dst.GetRow() - src.GetRow();				  //row desired move
	int horizontal_diff = dst.GetCol() - src.GetCol();			 //col desired move
	return abs(verctical_diff) <= 1 && abs(horizontal_diff) <= 1;	//check for if the king moved more than 1 square (he cant)
}

//getter
char King::GetPieceType()
{
	return 'k';
}
