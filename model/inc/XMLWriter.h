#ifndef CS240_XMLWriter_H
#define CS240_XMLWriter_H

#include <deque>
#include "Board.h"
#include <string>

class XMLWriter {

	public:
		XMLWriter();
		~XMLWriter();

		/**
		 * When given a location to save (string) a deque of Move objects (history)
		 * and a Board pointer it writes the current game's status and history to
		 * the location in XML format
		 */
		bool Write(string & saveFile, deque<Move> moves, Board* board);

	private:
		void WriteBoard(Board* board, ofstream * output);
		void WriteHistory(deque<Move> moves, ofstream * output);
		string GetTypeOfPiece (Type type);
		string GetColorOfPiece (PC col);
		string GetColorOfCaptured (PC col);
};

#endif
