#include "Location.h"

Location::Location(char col, char row)
{
	this->SetCol(col);
	this->SetRow(row);
}


Location::~Location() {}

int Location::GetRow()
{
	return this->_row;
}

int Location::GetCol()
{
	return this->_col;
}

// Function to set the row of a Location object.
// row is the new row value for the object.
void Location::SetRow(char row)
{
	// Check if the new row value is within the legal range for the board.
	if (row >= this->MIN_ROW && row <= this->MAX_ROW)
	{
		// If it is, set the row member variable to the zero-indexed value of the new row.
		this->_row = row - this->MIN_ROW;
	}
	else
	{
		// If the new row value is not within the legal range, throw an exception.
		throw ILLEGAL_INDEX;
	}
}


// Function to set the column of a Location object.
// col is the new column value for the object.
void Location::SetCol(char col)
{
	// Check if the new column value is within the legal range for the board.
	if (col >= this->MIN_COL && col <= this->MAX_COL)
	{
		// If it is, set the col member variable to the zero-indexed value of the new column.
		this->_col = col - this->MIN_COL;
	}
	else
	{
		// If the new column value is not within the legal range, throw an exception.
		throw ILLEGAL_INDEX;
	}
}
