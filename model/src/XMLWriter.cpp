#include "XMLWriter.h"
#include "Piece.h"
#include <cstring>
#include <string>
#include <fstream>
#include "CS240Exception.h"

//------------------------------------------------------------------------------------------------
XMLWriter::XMLWriter() {
}

//------------------------------------------------------------------------------------------------
XMLWriter::~XMLWriter() {
}

//------------------------------------------------------------------------------------------------
bool XMLWriter::Write(string & saveLocation, deque<Move> moves, Board* board) {
	
	char* o = new char[saveLocation.size()+1];
 	strcpy (o, saveLocation.c_str());

	ofstream output;
	output.open(o);
	if (!output.is_open()) {
		delete [] o;
		return false;
	}

	output << "<chessgame>" << endl;
	output << "\t<board>" << endl;
	WriteBoard(board, &output);
	output << "\t</board>" << endl;

	output << "\t<history>" << endl;
	WriteHistory(moves, &output);
	output << "\t</history>" << endl;
	output << "</chessgame>" << endl;

	output.close();
	delete [] o;
	return true;
}

//------------------------------------------------------------------------------------------------
void XMLWriter::WriteBoard(Board* board, ofstream * output) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* p = board->GetPieceAt(i, j);
			if (p != NULL) {
				*output << "\t\t<piece type=\"" << GetTypeOfPiece(p->GetType());
				*output << "\" color=\"" << GetColorOfPiece(p->GetColor());
				*output << "\" row=\"" << p->GetPosition()->GetRow();
				*output << "\" column=\"" << p->GetPosition()->GetCol();
				*output << "\"/>" << endl;
			}
		}
	}
}

//------------------------------------------------------------------------------------------------
void XMLWriter::WriteHistory(deque<Move> moves, ofstream * output) {

	while (!moves.empty()) {
		Move m = moves.back();
		moves.pop_back();
	
		*output << "\t<move>" << endl;

		// Starting Position
		*output << "\t\t\t<piece type=\"" << GetTypeOfPiece(m.GetType());
		*output << "\" color=\"" << GetColorOfPiece(m.GetColor());
		*output << "\" row=\"" << m.GetStart().GetRow();
		*output << "\" column=\"" << m.GetStart().GetCol();
		*output << "\"/>" << endl;

		// Ending Position
		*output << "\t\t\t<piece type=\"" << GetTypeOfPiece(m.GetType());
		*output << "\" color=\"" << GetColorOfPiece(m.GetColor());
		*output << "\" row=\"" << m.GetEnd().GetRow();
		*output << "\" column=\"" << m.GetEnd().GetCol();
		*output << "\"/>" << endl;

		// Captured Piece if applicable
		if (m.GetCaptured() != NOTYPE) {
			*output << "\t\t\t<piece type=\"" << GetTypeOfPiece(m.GetCaptured());
			*output << "\" color=\"" << GetColorOfCaptured(m.GetColor());
			*output << "\" row=\"" << m.GetEnd().GetRow();
			*output << "\" column=\"" << m.GetEnd().GetCol();
			*output << "\"/>" << endl;
		}

		*output << "\t</move>" << endl;
	}
}

//------------------------------------------------------------------------------------------------
string XMLWriter::GetTypeOfPiece (Type type) {
	if (type == PAWN)
		return "pawn";
	else if (type == KNIGHT)
		return "knight";
	else if (type == BISHOP)
		return "bishop";
	else if (type == ROOK)
		return "rook";
	else if (type == QUEEN)
		return "queen";
	else if (type == KING)
		return "king";
	else
		return "error";
}

//------------------------------------------------------------------------------------------------
string XMLWriter::GetColorOfPiece (PC col) {
	if (col == WHITE)
		return "white";
	else
		return "black";
}

//------------------------------------------------------------------------------------------------
string XMLWriter::GetColorOfCaptured (PC col) {
	if (col == WHITE)
		return "black";
	else
		return "white";
}
//------------------------------------------------------------------------------------------------
