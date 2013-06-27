#ifndef CS240_QUEEN_H
#define CS240_QUEEN_H
#include "Piece.h"

class Queen : public Piece {

	public:
		Queen(PC col, int r, int c);
		~Queen();

		/**
		 * Returns all moves for a Queen
		 * Note: this includes off-board and in-check moves
		 */
		vector<Position> GetValidMoves(Board* board);
};

#endif
