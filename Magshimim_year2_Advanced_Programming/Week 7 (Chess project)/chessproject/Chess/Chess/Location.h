#pragma once
#include "stdafx.h"

using std::string;

class Location
{
private:

	int _col;
	int _row;
	
public:

	static const char MIN_ROW = '1';
	static const char MAX_ROW = '8';
	static const char MIN_COL = 'a';
	static const char MAX_COL = 'h';

	Location(char col, char row);
	~Location();
	int GetRow();
	int GetCol();
	void SetRow(char row);
	void SetCol(char col);

};
	