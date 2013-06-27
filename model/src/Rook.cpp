#include "Rook.h"
#include "Board.h"


//------------------------------------------------------------------------------------------------
Rook::Rook(PC col, int r, int c) : Piece(ROOK, col, r, c) {
}

//------------------------------------------------------------------------------------------------
Rook::~Rook() {
}

//------------------------------------------------------------------------------------------------
vector<Position> Rook::GetValidMoves(Board* board) {

	vector<Position> vec;
	Position* curPos = this->GetPosition();
	int row = curPos->GetRow();
	int col = curPos->GetCol();

	// Up
	while (row > 0) {
		if (board->GetPieceAt(--row, col) == NULL) {
			Position pos(row, col);
			vec.push_back(pos);
		}
	
		else if ((board->GetPieceAt(row, col))->GetColor() != this->GetColor()) {
			
			Position pos(row, col);
			vec.push_back(pos);
			break;
		}
		else 
			break;
	}

	// Down
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (row < 7) {
		if (board->GetPieceAt(++row, col) == NULL) { // Blank square
			Position pos(row, col);
			vec.push_back(pos);
		}
	
		else if ((board->GetPieceAt(row, col))->GetColor() != this->GetColor()) { //enemy
			
			Position pos(row, col);
			vec.push_back(pos);
			break;
		}
		else // My piece
			break;
	}

	// Left
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (col > 0) {
		if (board->GetPieceAt(row, --col) == NULL) {
			Position pos(row, col);
			vec.push_back(pos);
		}
		else if ((board->GetPieceAt(row, col))->GetColor() != this->GetColor()) {
			
			Position pos(row, col);
			vec.push_back(pos);
			break;
		}
		else 
			break;
	}

	// Right
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (col < 7) {
		if (board->GetPieceAt(row, ++col) == NULL) {
			Position pos(row, col);
			vec.push_back(pos);
		}
		else if ((board->GetPieceAt(row, col))->GetColor() != this->GetColor()) {
			Position pos(row, col);
			vec.push_back(pos);
			break;
		}
		else 
			break;
	}

	return vec;
}
//------------------------------------------------------------------------------------------------
