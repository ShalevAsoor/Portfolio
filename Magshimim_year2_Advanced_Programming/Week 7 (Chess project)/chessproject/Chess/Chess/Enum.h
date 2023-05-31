#pragma once

enum MoveResult
{
	LEGAL_MOVE,
	CHECK,
	EMPTY_SQUARE,
	TAKEN_SQUARE,
	SELF_CHECK,
	ILLEGAL_INDEX,
	ILLEGAL_MOVE,
	SAME_SQUARE,
};

enum Side : bool
{
	W = true,
	B = false
};
