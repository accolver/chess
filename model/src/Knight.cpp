#include "Knight.h"
#include "Board.h"

//------------------------------------------------------------------------------------------------
Knight::Knight(PC col, int r, int c) : Piece(KNIGHT, col, r, c) {
}
//------------------------------------------------------------------------------------------------

Knight::~Knight() {
}

//------------------------------------------------------------------------------------------------
vector<Position> Knight::GetValidMoves(Board* board) {

	vector<Position> vec; 
	Position* curPos = this->GetPosition();
	int row = curPos->GetRow();
	int col = curPos->GetCol();

	if (board->GetPieceAt(row - 1, col - 2) == NULL || 
	    (board->GetPieceAt(row - 1, col - 2))->GetColor() != this->GetColor()) {
		Position pos(row - 1, col - 2);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row - 1, col + 2) == NULL || 
	    (board->GetPieceAt(row - 1, col + 2))->GetColor() != this->GetColor()) {
		Position pos(row - 1, col + 2);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row + 1, col - 2) == NULL || 
	    (board->GetPieceAt(row + 1, col - 2))->GetColor() != this->GetColor()) {
		Position pos(row + 1, col - 2);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row + 1, col + 2) == NULL || 
	    (board->GetPieceAt(row + 1, col + 2))->GetColor() != this->GetColor()) {
		Position pos(row + 1, col + 2);
		vec.push_back(pos);
	}
	
	if (board->GetPieceAt(row - 2, col - 1) == NULL || 
	    (board->GetPieceAt(row - 2, col - 1))->GetColor() != this->GetColor()) {
		Position pos(row - 2, col - 1);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row - 2, col + 1) == NULL || 
	    (board->GetPieceAt(row - 2, col + 1))->GetColor() != this->GetColor()) {
		Position pos(row - 2, col + 1);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row + 2, col - 1) == NULL || 
	    (board->GetPieceAt(row + 2, col - 1))->GetColor() != this->GetColor()) {
		Position pos(row + 2, col - 1);
		vec.push_back(pos);
	}
	if (board->GetPieceAt(row + 2, col + 1) == NULL || 
	    (board->GetPieceAt(row + 2, col + 1))->GetColor() != this->GetColor()) {
		Position pos(row + 2, col + 1);
		vec.push_back(pos);
	}

	return vec;
}
//------------------------------------------------------------------------------------------------
