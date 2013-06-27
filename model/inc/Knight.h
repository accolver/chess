#ifndef CS240_KNIGHT_H
#define CS240_KNIGHT_H
#include "Piece.h"

class Knight : public Piece {

	public:
		Knight(PC col, int r, int c);
		~Knight();

		/**
		 * Returns all moves for a Knight
		 * Note: this includes off-board and in-check moves
		 */
		vector<Position> GetValidMoves(Board* board);
};

#endif
