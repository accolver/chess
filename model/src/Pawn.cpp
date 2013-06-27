#include "Pawn.h"
#include "Board.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------
Pawn::Pawn(PC col, int r, int c) : Piece(PAWN, col, r, c) {
}

//------------------------------------------------------------------------------------------------
Pawn::~Pawn() {
}

//------------------------------------------------------------------------------------------------
vector<Position> Pawn::GetValidMoves(Board* board) {
	
	vector<Position> vec;
	Position* curPos = this->GetPosition();
	int row = curPos->GetRow();
	int col = curPos->GetCol();


	if (this->GetColor() == WHITE) {
		// Checks square immediately in front of the pawn
		if (board->GetPieceAt(row - 1, col) == NULL) {
			
			// Checks twos squares in front of the pawn
			if (board->GetPieceAt(row - 2, col) == NULL && row == 6) {
				Position pos(row - 2, col);
				vec.push_back(pos);
			}

			Position pos(row - 1, col);
			vec.push_back(pos);
		}

		if (board->GetPieceAt(row - 1, col - 1) != NULL && 
		    (board->GetPieceAt(row - 1, col - 1))->GetColor() != this->GetColor()) {
			Position pos(row - 1, col - 1);
			vec.push_back(pos);
		}
		
		if (board->GetPieceAt(row - 1, col + 1) != NULL && 
		    (board->GetPieceAt(row - 1, col + 1))->GetColor() != this->GetColor()) {
			Position pos(row - 1, col + 1);
			vec.push_back(pos);
		}
	}

	else {
		if (board->GetPieceAt(row + 1, col) == NULL) {
			
			if (board->GetPieceAt(row + 2, col) == NULL && row == 1) {
				Position pos(row + 2, col);
				vec.push_back(pos);
			}

			Position pos(row + 1, col);
			vec.push_back(pos);
		}
		
		if (board->GetPieceAt(row + 1, col - 1) != NULL && 
		    (board->GetPieceAt(row + 1, col - 1))->GetColor() != this->GetColor()) {
			Position pos(row + 1, col - 1);
			vec.push_back(pos);
		}
		
		if (board->GetPieceAt(row + 1, col + 1) != NULL && 
		    (board->GetPieceAt(row + 1, col + 1))->GetColor() != this->GetColor()) {
			Position pos(row + 1, col + 1);
			vec.push_back(pos);
		}
	}

	return vec;
}
//------------------------------------------------------------------------------------------------
