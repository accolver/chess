#ifndef CS240_BISHOP_H
#define CS240_BISHOP_H
#include "Piece.h"

class Bishop : public Piece {

	public:
		Bishop(PC col, int r, int c);
		~Bishop();

		/**
		 * Returns all moves for a Bishop
		 * Note: this includes off-board and in-check moves
		 */
		vector<Position> GetValidMoves(Board* board);
};

#endif
