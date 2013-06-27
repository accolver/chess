#ifndef CS240_Move_H
#define CS240_Move_H

#include <string>
#include "Piece.h"


class Move {

	public:
		Move();
		~Move();

		/**
		 * Sets the Start Position object
		 */
		void SetStart(Position p);

		/**
		 * Returns the Start Position object
		 */
		Position GetStart();

		/**
		 * Sets the End Position object
		 */
		void SetEnd(Position p);

		/**
		 * Returns the End Position object
		 */
		Position GetEnd();

		/**
		 * Sets the Color of the piece being moved
		 */
		void SetColor(PC c);

		/**
		 * Returns the Color of the piece being moved
		 */
		PC GetColor();

		/**
		 * Sets the Type of the piece being moved
		 */
		void SetType(Type t);

		/**
		 * Returns the Type of the piece being moved
		 */
		Type GetType();

		/**
		 * Sets the Type of piece being captured (if none set to NOTYPE)
		 */
		void SetCaptured(Type t);

		/**
		 * Returns the Type of piece being captured (if none it should return NOTYPE)
		 */
		Type GetCaptured();

		/**
		 * Resets the Move object to its default values
		 */
		void Reset();
	
	private :
		Type type;
		PC color;
		Position start;
		Position end;
		Type capturedPiece;

};

#endif
