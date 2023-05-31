#include "Pawn.h"

Pawn::Pawn(Side color): Piece(color)
{
	this->moved = false;
}

Pawn::~Pawn() {}

//This function determines the validity of a pawn's move on a chess board. 
//It returns a boolean value indicating whether the move is allowed.
bool Pawn::MoveCheck(Location src, Location dst, Piece* board_arr[][8]) {
    // Calculate the differences in rows and columns between the source and destination locations
    int verctical_diff = src.GetRow() - dst.GetRow();
    int horizontal_diff = src.GetCol() - dst.GetCol();

    // If the pawn is white
    if (this->GetColor()) {
        // If the destination is empty
        if (board_arr[dst.GetRow()][dst.GetCol()] == nullptr) {
            // If this is the pawn's first move, it can move 1 or 2 spaces forward
            if (!this->moved) {
                this->moved = true;
                return 1 <= verctical_diff && verctical_diff <= 2 && horizontal_diff == 0;
            }
            // Otherwise, it can only move 1 space forward
            return verctical_diff == 1 && horizontal_diff == 0;
        }
        // If the destination is not empty and the pawn is moving diagonally, it is a valid capture move
        if (abs(horizontal_diff) == 1 && verctical_diff == 1) {
            this->moved = true;
            return true;
        }
        // Otherwise, the move is invalid
        return false;
    }

    // If the pawn is black, the logic is the same as above but with the signs reversed
    if (board_arr[dst.GetRow()][dst.GetCol()] == nullptr) {
        if (!this->moved) {
            this->moved = true;
            return -1 >= verctical_diff && verctical_diff >= -2 && horizontal_diff == 0;
        }
        return verctical_diff == -1 && horizontal_diff == 0;
    }
    if (abs(horizontal_diff) == 1 && verctical_diff == -1) {
        this->moved = true;
        return true;
    }
    return false;
}


	
//getter
char Pawn::GetPieceType()
{
	return 'p';
}