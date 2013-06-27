#ifndef CS240_PAWN_H
#define CS240_PAWN_H
#include "Piece.h"

class Pawn : public Piece {

	public:
		Pawn(PC col, int r, int c);
		~Pawn();

		/**
		 * Returns all moves for a Pawn
		 * Note: this includes off-board and in-check moves
		 */
		vector<Position> GetValidMoves(Board* board);
};

#endif
