#ifndef CS240_Piece_H
#define CS240_Piece_H

#include "Position.h"
#include <vector>
class Board;
using namespace std;

enum PC {WHITE, BLACK, NOCOLOR};
enum Type {KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, NOTYPE};

class Piece {

	public:
		Piece(Type t, PC col, int r, int c);
		~Piece();
		Piece(const Piece & other);

		/*
		 * virtual method that can be called on all type of chess pieces, which
		 * then return a vector of their valid moves (Position objects)
		 * Note: Also returns off-board and in-check positions
		 */
		virtual vector<Position> GetValidMoves(Board* board) = 0;

		/*
		 * Returns the Type of the piece
		 */
		Type GetType();

		/*
		 * Returns the color (PC) of the piece
		 */
		PC GetColor();

		/*
		 * Sets the color (PC) of a piece
		 */
		void SetColor(PC c);

		/*
		 * Returns a Position object of a piece
		 */
		Position* GetPosition();


	private:
		Type type;
		Position pos;
		PC color;
};

#endif
