#ifndef CS240_XMLReader_H
#define CS240_XMLReader_H
#include <string>
#include <deque>
#include "Move.h"
#include "Piece.h"
#include "HTMLToken.h"
using namespace std;

class XMLReader {

	public:
		XMLReader();
		~XMLReader();

		/**
		 * Takes a string of a file and its path and then parses the saved chess
		 * game and returns a deque of Move objects
		 */
		deque<Move> Read(string & loadLocation);

	private:
		void ParseXML(string & xml);
		bool inBoard;
		bool inHistory;
		bool inMove;
		deque<Move> moves;;
		Move move;
		int moveNum;

		void HandleStart (HTMLToken t);
		void HandleEnd (HTMLToken t);
		PC GetColorByName(string color);
		Type GetTypeByName(string type);

};

#endif
