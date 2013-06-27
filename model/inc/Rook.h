#ifndef CS240_ROOK_H
#define CS240_ROOK_H
#include "Piece.h"

class Rook : public Piece {

	public:
		Rook(PC col, int r, int c);
		~Rook();

		/**
		 * Returns all moves for a Rook
		 * Note: this includes off-board and in-check moves
		 */	
		vector<Position> GetValidMoves(Board* board);
};

#endif
