#include "Board.h"

//ctor
// Constructor for the Board class. Initializes the board based on the input string.
Board::Board(const string init_board)
{
    int pos = 0;
    // Loop through each row of the board.
    for (char i = Location::MIN_ROW; i <= Location::MAX_ROW; ++i)
    {
        // Loop through each column of the board.
        for (char j = Location::MIN_COL; j <= Location::MAX_COL; ++j, ++pos)
        {
            // Create a piece at the current location based on the corresponding character in the init_board string.
            (*this)[Location(j, i)] = GetPieceType(init_board[pos]);
            std::cout << "created Piece " << init_board[pos] << " in " << j << i << std::endl;
        }
    }
    // Set the current player based on the last character in the init_board string.
    this->_turn = (init_board[pos] == '1') ? W : B;
}




// Function to move a piece from one location to another on the board.
// Returns a MoveResult enum value indicating the result of the move.
MoveResult Board::MovePiece(Location src, Location dst)
{
    // Get the source and destination pieces.
    Piece* src_piece = (*this)[src];
    Piece* dst_piece = (*this)[dst];

    // Check if there is a piece at the source location.
    if (src_piece == nullptr)
    {
        return EMPTY_SQUARE;
    }

    // Check if it is the current player's turn to move.
    Side src_side = src_piece->GetColor();
    if (src_side != this->_turn)
    {
        return EMPTY_SQUARE;
    }

    // Check if there is a piece at the destination location, and if it is an enemy piece.
    if (dst_piece != nullptr && dst_piece->GetColor() == src_side)
    {
        return TAKEN_SQUARE;
    }
    // Check if the source and destination are the same.
    else if (src_piece == dst_piece)
    {
        return SAME_SQUARE;
    }

    // Check if the move is valid for the source piece.
    if (!src_piece->MoveCheck(src, dst, this->_board_arr))
    {
        return ILLEGAL_MOVE;
    }

    // Temporary pointer to store the piece at the destination location.
    Piece* temp = dst_piece;
    // Make the move.
    (*this)[dst] = src_piece;
    (*this)[src] = nullptr;

    // Check if the move puts the current player's king in check.
    if (CheckCheck(src, dst, src_side))
    {
        // If it does, undo the move and return SELF_CHECK.
        (*this)[src] = (*this)[dst];
        (*this)[dst] = temp;
        return SELF_CHECK;
    }

    // Delete the destination piece (if it exists).
    delete temp;
    // Switch the current player.
    this->_turn = (Side)!this->_turn;
    // Check if the move puts the other player's king in check.
    if (CheckCheck(src, dst, (Side)!src_side))
    {
        return CHECK;
    }

    // If the move is valid and does not result in chess for either player, return LEGAL_MOVE.
    return LEGAL_MOVE;
}


// Function to check if a given player's king is in check.
// src and dst are the source and destination locations of the move that resulted in the potential check.
// side is the color of the player whose king needs to be checked.
bool Board::CheckCheck(Location src, Location dst, Side side)
{
    // Get the location of the king.
    Location king = this->GetKing(side);

    // Loop through each location on the board.
    for (char i = Location::MIN_ROW; i <= Location::MAX_ROW; ++i)
    {
        for (char j = Location::MIN_COL; j <= Location::MAX_COL; ++j)
        {
            Location loc(j, i);
            // If there is a piece at the current location and it is not on the same side as the player being checked,
            if ((*this)[loc] != nullptr && side != (*this)[loc]->GetColor())
            {
                // Check if the piece can attack the king.
                if ((*this)[loc]->MoveCheck(loc, king, this->_board_arr))
                {
                    // If it can, return true.
                    return true;
                }
            }
        }
    }
    // If no pieces can attack the king, return false.
    return false;
}


// GetPieceType creates a new chess piece object of the appropriate type based on the character representation of the piece.
Piece* Board::GetPieceType(char p)
{
	Side side = (p > 'Z') ? B : W;
	p = toupper(p);

	switch (p)
	{
	case 'K': return new King(side);
	case 'R': return new Rook(side);
	case 'B': return new Bishop(side);
    case 'Q': return new Queen(side);
    case 'P': return new Pawn(side);
    case 'N': return new Knight(side);
	case '#': return nullptr;
	default: return nullptr;
	}
}

Piece *& Board::operator[](Location loc)
{
	return this->_board_arr[loc.GetRow()][loc.GetCol()];
}



// Function to get the location of a player's king on the board.
// side is the color of the player whose king needs to be found.
Location Board::GetKing(Side side)
{
    // Loop through each row and column of the board.
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            // Check if there is a piece at the current location, and if it is a king of the correct color.
            if (this->_board_arr[row][col] != nullptr && side == this->_board_arr[row][col]->GetColor() && this->_board_arr[row][col]->GetPieceType() == 'k')
            {
                // If so, return the Location object representing the location of the king.
                return Location(col + Location::MIN_COL, row + Location::MIN_ROW);
            }
        }
    }
    // If the king is not found, return an invalid location.
    return Location('a','1');
}


