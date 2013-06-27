#ifndef CS240_Board_H
#define CS240_Board_H

#include "Piece.h"
#include "King.h"
#include "Move.h"
#include "UnitTest.h"
#include "ChessGuiDefines.h"
#include <vector>

class Board {

	public:
		Board();
		~Board();

		/**
		 * Sets up a standard chess board for a new game
		 */
		void SetUpBoard();
	
		/**
		 * Returns a set of all valid moves (on/off) board
		 */
		vector<Position> GetValidMovesForPiece(int row, int col, PC curPlayersColor);

		/**
		 * Returns the Piece pointer corresponding to a board position (row, and column)
		 */
		Piece* GetPieceAt(int row, int col);

		/**
		 * Updates the board's Piece pointers based on the Move object (param) in the 
		 * normal event of a move
		 */
		void UpdateBoard(Move* move);

		/**
		 * Updates the board's Piece pointers based on the Move object (param) in the
		 * event of an undo
		 */
		void UpdateBoardUndo(Move* move);

		/**
		 * Returns a pointer to the White player's King
		 */
		King* GetWhiteKing();

		/**
		 * Returns a pointer to the Black player's King
		 */
		King* GetBlackKing();

		static bool Test(ostream & os);


	private :
		Piece* grid[8][8];
		King* whiteKing;
		King* blackKing;

		
		/**
		 * Removes all pieces of the board (model only, not view)
		 */
		void ClearBoard();

		/**
		 * Removes all moves if they're off the board and returns a set
		 * containing only valid-on-board moves
		 */
		vector<Position> RemoveOffBoardMoves(vector<Position> v);
		
		/**
		 * Removes all moves for a piece if they leave that players King in check
		 */
		vector<Position> RemoveMovesThatLeaveInCheck(
			vector<Position> v, Piece* p, PC curPlayersColor);



};

#endif
