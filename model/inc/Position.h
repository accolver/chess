#ifndef CS240_POSITION_H
#define CS240_POSITION_H

class Position {

	public:
		Position();
		Position(int r, int c);
		~Position();
	
		/**
		 * Copy Constructor
		 */
		Position(const Position & other);

		/**
		 * Returns the Row of the Position object
		 */
		int GetRow();

		/**
		 * Returns the Column of the Position object
		 */
		int GetCol();

		/**
		 * Sets the Row of the Position object
		 */
		void SetRow(int r);

		/**
		 * Sets the Column of the Position object
		 */
		void SetCol(int c);

	private:
		int row;
		int col;

};

#endif
