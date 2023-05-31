#include "Piece.h"

//ctor
Piece::Piece(Side color)
{
	this->_color = color;
}

//dtor
Piece::~Piece() {}

//getter
Side Piece::GetColor()
{
	return this->_color;
}

//Check if the given move from location src to location dst is a straight move(either horizontal or vertical) on the board represented by board_arr.
//Returns true if the move is straightand there are no pieces blocking the way, and false otherwise.

bool Piece::moveStraight(Location src, Location dst, Piece* board_arr[][8]) {
    // Check if the move is straight (either horizontal or vertical)
    if (src.GetRow() != dst.GetRow() && src.GetCol() != dst.GetCol()) {
        return false;
    }

    int i, j;
    int move_by_row = 0, move_by_col = 0;
    // Determine the direction of the move (for both row and column)
    if (src.GetRow() < dst.GetRow()) {
        move_by_row = 1;
    }
    else if (src.GetRow() > dst.GetRow()) {
        move_by_row = -1;
    }
    if (src.GetCol() < dst.GetCol()) {
        move_by_col = 1;
    }
    else if (src.GetCol() > dst.GetCol()) {
        move_by_col = -1;
    }

    // Check if there are any pieces blocking the way
    i = src.GetRow() + move_by_row;
    j = src.GetCol() + move_by_col;
    while (i != dst.GetRow() || j != dst.GetCol()) {
        if (board_arr[i][j] != nullptr) {
            return false;
        }
        i += move_by_row;
        j += move_by_col;
    }

    return true;
}




// Function to check if a piece can move diagonally to a destination location.
// src is the source location of the piece.
// dst is the destination location of the piece.
// board_arr is the array representing the game board.
bool Piece::moveDiagonal(Location src, Location dst, Piece* board_arr[][8]) {
    // Check if the move is diagonal (row difference is equal to column difference)
    int row_diff = dst.GetRow() - src.GetRow();
    int col_diff = dst.GetCol() - src.GetCol();
    if (abs(row_diff) != abs(col_diff)) {
        // If the row and column differences are not equal, the move is not diagonal.
        return false;
    }

    // Calculate the direction to move in both rows and columns.
    int move_by_row = row_diff / abs(row_diff);
    int move_by_col = col_diff / abs(col_diff);

    // Check if there are any pieces blocking the way.
    int i = src.GetRow() + move_by_row;
    int j = src.GetCol() + move_by_col;
    // Keep moving in the calculated direction until the destination is reached.
    while (i != dst.GetRow() || j != dst.GetCol()) {
        // If there is a piece at the current location, the move is not valid.
        if (board_arr[i][j] != nullptr) {
            return false;
        }
        // Update the current row and column.
        i += move_by_row;
        j += move_by_col;
    }

    // If the loop finishes without returning false, the move is valid.
    return true;
}

