#ifndef CS240_KING_H
#define CS240_KING_H
#include "Piece.h"

class King : public Piece {

	public:
		King(PC col, int r, int c);
		~King();

		/*
		 * Returns a vector of Position objects that the King can make
		 * Note: this includes off-board and in-check moves
		 */
		vector<Position> GetValidMoves(Board* board);

		/*
		 * Given a board and position on the board it determines if that location
		 * is in check
		 */
		bool InCheck(int r, int c, Board* b);

	private:

		bool QueenBishopCheck(int r, int c, Board* b);
		bool QueenRookCheck(int r, int c, Board* b);
		bool KnightCheck(int r, int c, Board* b);
		bool PawnCheck(int r, int c, Board* b);
		bool KingCheck(int r, int c, Board* b);
};

#endif
