#include "Queen.h"
#include "Board.h"

//------------------------------------------------------------------------------------------------
Queen::Queen(PC col, int r, int c) : Piece(QUEEN, col, r, c) {
}

//------------------------------------------------------------------------------------------------
Queen::~Queen() {
}

//------------------------------------------------------------------------------------------------
vector<Position> Queen::GetValidMoves(Board* board) {

	vector<Position> vec;
	Position* curPos = this->GetPosition();
	int row = curPos->GetRow();
	int col = curPos->GetCol();

	// Up and Left
	while (row > 0 && col > 0) {
		if (board->GetPieceAt(--row, --col) == NULL) {
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

	// Up and Right
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (row > 0 && col < 7) {
		if (board->GetPieceAt(--row, ++col) == NULL) {
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

	// Down and Left
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (row < 7 && col > 0) {
		if (board->GetPieceAt(++row, --col) == NULL) {
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

	// Down and Right
	row = curPos->GetRow();
	col = curPos->GetCol();
	while (row < 7 && col < 7) {
		if (board->GetPieceAt(++row, ++col) == NULL) {
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

	// Up
	row = curPos->GetRow();
	col = curPos->GetCol();
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
		if (board->GetPieceAt(++row, col) == NULL) {
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
